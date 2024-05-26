#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct UserData {
    string username;
    string password;
    string name;
    string phoneNum;
};

struct infokamar {
    string kosan;
    int lantai;
    int nomorKamar;
    string fasilitas;
    double harga;
    bool isAvailable;
    string pemilik;
};

// Deklarasi kamar-kamar
infokamar kamar1 = {"Putri", 1, 1, "WC berada di dalam, AC, Kasur ukuran 120x200", 1500000, true};
infokamar kamar2 = {"Putri", 1, 2, "WC berada di dalam, Kipas Angin, Kasur ukuran 90x200", 1000000, true};
infokamar kamar3 = {"Putri", 1, 3, "WC berada di dalam, AC, Kasur ukuran 120x200", 1500000, true};
infokamar kamar4 = {"Putri", 1, 4, "WC berada di dalam, Kipas Angin, Kasur ukuran 90x200", 1000000, true};
infokamar kamar5 = {"Putri", 1, 5, "WC berada di dalam, AC, Kasur ukuran 120x200", 1500000, true};
infokamar kamar6 = {"Putri", 2, 6, "WC berada di dalam, AC, Kasur ukuran 120x200", 1500000, true};
infokamar kamar7 = {"Putri", 2, 7, "WC berada di dalam, Kipas Angin, Kasur ukuran 90x200", 1000000, true};
infokamar kamar8 = {"Putri", 2, 8, "WC berada di dalam, AC, Kasur ukuran 120x200", 1500000, true};
infokamar kamar9 = {"Putri", 2, 9, "WC berada di dalam, Kipas Angin, Kasur ukuran 90x200", 1000000, true};
infokamar kamar10 = {"Putri", 2, 10, "WC berada di dalam, AC, Kasur ukuran 120x200", 1500000, true};

//array kamar
infokamar kamars[] = {kamar1, kamar2, kamar3, kamar4, kamar5, kamar6, kamar7, kamar8, kamar9, kamar10};

// Fungsi untuk menampilkan informasi kamar
void displayKamar(const infokamar& kamar) {
    cout << "Kos " << kamar.kosan << ":" << endl;
    cout << "Lantai " << kamar.lantai << " : Nomor Kamar (" << kamar.nomorKamar << ")" << endl;
    cout << "Fasilitas Yang Didapat : " << kamar.fasilitas << endl;
    cout << "Harga sewa perbulan : Rp. " << fixed << setprecision(2) << kamar.harga << endl;
    cout << "Status: " << (kamar.isAvailable ? "Kosong" : "Terambil") << endl;
    cout << "-------------------------------------" << endl;
}

// Fungsi untuk menyimpan status kamar ke dalam file teks
void saveStatusToFile(const infokamar kamar[], int jumlahKamar) {
    ofstream outFile("status_kamar.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < jumlahKamar; ++i) {
            outFile << kamar[i].kosan << " " 
                    << kamar[i].lantai << " " << kamar[i].nomorKamar << " " 
                    << kamar[i].fasilitas << " " << kamar[i].harga << " "
                    << (kamar[i].isAvailable ? "Kosong" : "Terambil");
            if (!kamar[i].isAvailable) {
                outFile << " " << kamar[i].pemilik;
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Status kamar berhasil disimpan ke dalam file status_kamar.txt." << endl;
    } else {
        cout << "Gagal menyimpan status kamar." << endl;
    }
}


void loadStatusFromFile(infokamar kamar[], int jumlahKamar) {
    ifstream inFile("status_kamar.txt");
    if (inFile.is_open()) {
        string line;
        for (int i = 0; i < jumlahKamar && getline(inFile, line); ++i) {
            stringstream ss(line);
            string kosan, fasilitas, status, pemilik;
            int lantai, nomorKamar;
            double harga;
            ss >> kosan >> lantai >> nomorKamar;
            ss.ignore(); // ignore space before fasilitas
            getline(ss, fasilitas, ','); // read fasilitas until comma
            ss >> harga >> status;
            kamar[i].kosan = kosan;
            kamar[i].lantai = lantai;
            kamar[i].nomorKamar = nomorKamar;
            kamar[i].fasilitas = fasilitas;
            kamar[i].harga = harga;
            kamar[i].isAvailable = true;
            if (!kamar[i].isAvailable) {
                ss >> pemilik;
                kamar[i].pemilik = pemilik;
            } else {
                kamar[i].pemilik.clear();
            }
        }
        inFile.close();
        cout << "Status kamar berhasil dimuat dari file status_kamar.txt." << endl;
    } else {
        cout << "Gagal membuka file status_kamar.txt. Menggunakan status default." << endl;
    }
}


// Fungsi untuk memperbarui status kamar
void updateKamar(infokamar kamar[], int jumlahKamar, infokamar& kamarToUpdate, bool status, const string& pemilik = "") {
    kamarToUpdate.isAvailable = status;
    if (!status) {
        kamarToUpdate.pemilik = pemilik;
    } else {
        kamarToUpdate.pemilik.clear();
    }
    saveStatusToFile(kamar, jumlahKamar);
}

// Fungsi untuk menampilkan semua kamar
void displayAllKamar() {
    for (const auto& kamar : kamars) {
        displayKamar(kamar);
    }
}

void registerRoom(infokamar kamar[], int jumlahKamar) {
    int lantai, nomorKamar;
    string pemilik;

    do {
        cout << "Masukkan lantai (angka): ";
        while (!(cin >> lantai)) {
            cout << "Input harus berupa angka. Silakan masukkan input yang benar." << endl;
            cin.clear(); // Membersihkan status error pada cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan karakter yang tersisa pada buffer
        }
    } while (lantai <= 0); // Memastikan lantai yang dimasukkan adalah bilangan bulat positif

     do {
        cout << "Masukkan nomor kamar (angka): ";
        while (!(cin >> nomorKamar)) {
            cout << "Input harus berupa angka. Silakan masukkan input yang benar." << endl;
            cin.clear(); // Membersihkan status error pada cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan karakter yang tersisa pada buffer
        }
    } while (nomorKamar <= 0); // Memastikan nomor kamar yang dimasukkan adalah bilangan bulat positif

    cin.ignore(); // Membersihkan buffer
    cout << "Masukkan nama pemilik: ";
    getline(cin, pemilik);


    bool kamarDitemukan = false;
    for (int i = 0; i < jumlahKamar; ++i) {
        if (kamar[i].lantai == lantai && kamar[i].nomorKamar == nomorKamar) {
            kamarDitemukan = true;
            if (kamar[i].isAvailable) {
                // Jika kamar tersedia, daftarkan pengguna ke kamar tersebut
                kamar[i].isAvailable = false;
                kamar[i].pemilik = pemilik;
                cout << "Anda berhasil mendaftar ke kamar " << kamar[i].nomorKamar << " di lantai " << kamar[i].lantai << "." << endl;
                // Simpan perubahan ke file
                saveStatusToFile(kamar, jumlahKamar);
            } else {
                // Jika kamar tidak tersedia, periksa apakah pemilik kamar sama dengan yang baru mendaftar
                if (kamar[i].pemilik == pemilik) {
                    cout << "Anda sudah terdaftar sebagai pemilik kamar ini." << endl;
                } else {
                    cout << "Kamar ini sudah terisi oleh pemilik lain." << endl;
                }
            }
            break;
        }
    }

    if (!kamarDitemukan) {
        cout << "Kamar tidak ditemukan." << endl;
    }
}

void MenuUser(const string& username) {
    char pilihan;
    
     while (true) {
        cout << "--------------------------------------------" << endl;
        cout << ":::   SELAMAT DATANG DI KOS MELATI JAYA  :::" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "================ Menu User =================" << endl;
        cout << "| 1. Lihat Daftar Kamar                    |" << endl;
        cout << "| 2. Daftar                                |" << endl;
        cout << "| 3. Keluar                                |" << endl;
        cout << "================ Menu User ================" << endl;

        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                displayAllKamar();
                break;
            case '2':
                registerRoom(kamars, sizeof(kamars) / sizeof(kamars[0]));
                break;
            case '3':
                cout << "Anda telah keluar dari menu user" << endl; 
                return;
            default:
                cout << "Pilihan tidak valid, Silakan masukkan pilihan dengan benar" << endl;
                break;
        }
    }
}

void deleteRoom(infokamar kamar[], int jumlahKamar) {
    int lantai, nomorKamar;

    cout << "Masukkan lantai kamar yang akan dihapus: ";
    while (!(cin >> lantai)) {
        cout << "Input tidak valid. Masukkan angka." << endl;
        cin.clear(); // reset status error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
    }

    cout << "Masukkan nomor kamar yang akan dihapus: ";
    while (!(cin >> nomorKamar)) {
        cout << "Input tidak valid. Masukkan angka." << endl;
        cin.clear(); // reset status error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
    }
    
    // Periksa apakah kamar yang akan dihapus ada dalam daftar
    bool kamarDitemukan = false;
    for (int i = 0; i < jumlahKamar; ++i) {
        if (kamar[i].lantai == lantai && kamar[i].nomorKamar == nomorKamar) {
            kamarDitemukan = true;
            // Lakukan penghapusan kamar dari daftar
            kamar[i].kosan = "";
            kamar[i].lantai = 0;
            kamar[i].nomorKamar = 0;
            kamar[i].fasilitas = "";
            kamar[i].harga = 0;
            kamar[i].isAvailable = true;
            kamar[i].pemilik = "";
            cout << "Kamar dengan lantai " << lantai << " dan nomor " << nomorKamar << " telah dihapus." << endl;

            // Hapus data dari file
            ifstream inFile("status_kamar.txt");
            ofstream outFile("temp.txt");

            if (!inFile.is_open() || !outFile.is_open()) {
                cout << "Gagal membuka file." << endl;
                return;
            }

            string line;
            while (getline(inFile, line)) {
                // Jika bukan baris yang ingin dihapus, tulis kembali ke file sementara
                stringstream ss(line);
                string kosanFile;
                int lantaiFile, nomorKamarFile;
                string status, pemilik;

                ss >> kosanFile >> lantaiFile >> nomorKamar >> status;
                if (lantaiFile != lantai && nomorKamarFile != nomorKamar) {
                    outFile << line << endl;
                }
            }

            inFile.close();
            outFile.close();

            // Hapus file asli dan ubah nama file sementara menjadi nama file asli
            remove("status_kamar.txt");
            rename("temp.txt", "status_kamar.txt");

            break;
        }
    }

    if (!kamarDitemukan) {
        cout << "Kamar tidak ditemukan." << endl;
    }
}

void updateRoomStatus(infokamar kamar[], int jumlahKamar) {
    int lantai, nomorKamar;
    bool newStatus;

    do {
        cout << "Masukkan lantai kamar yang akan diperbarui statusnya (angka): ";
        cin >> lantai;
        if (cin.fail()) {
            cout << "Input harus berupa angka. Silakan masukkan input yang benar." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cin.fail());

    do {
        cout << "Masukkan nomor kamar yang akan diperbarui statusnya (angka): ";
        cin >> nomorKamar;
        if (cin.fail()) {
            cout << "Input harus berupa angka. Silakan masukkan input yang benar." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cin.fail());

    do {
        cout << "Masukkan status baru (0 untuk terisi, 1 untuk kosong): ";
        cin >> newStatus;
        if (cin.fail() || (newStatus != 0 && newStatus != 1)) {
            cout << "Input harus berupa angka 0 atau 1. Silakan masukkan input yang benar." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cin.fail() || (newStatus != 0 && newStatus != 1));

    // Periksa apakah kamar yang akan diperbarui statusnya ada dalam daftar
    bool kamarDitemukan = false;
    for (int i = 0; i < jumlahKamar; ++i) {
        if (kamar[i].lantai == lantai && kamar[i].nomorKamar == nomorKamar) {
            kamarDitemukan = true;
            // Lakukan pembaruan status kamar
            updateKamar(kamar, jumlahKamar, kamar[i], newStatus);
            cout << "Status kamar dengan lantai " << lantai << " dan nomor " << nomorKamar << " berhasil diperbarui." << endl;
            break;
        }
    }

    if (!kamarDitemukan) {
        cout << "Kamar tidak ditemukan." << endl;
    }
}

void sortKamarByPrice(infokamar kamar[], int jumlahKamar) {
    // Algoritma Insertion Sort
    for (int i = 1; i < jumlahKamar; ++i) {
        infokamar key = kamar[i];
        int j = i - 1;

        // Pindahkan elemen-elemen kamar[0..i-1], yang lebih besar dari key, ke satu posisi ke depan dari posisi saat ini
        while (j >= 0 && kamar[j].harga > key.harga) {
            kamar[j + 1] = kamar[j];
            j = j - 1;
        }
        kamar[j + 1] = key;
    }

    // Tampilkan daftar kamar yang sudah diurutkan
    cout << "Daftar Kamar Setelah Diurutkan Berdasarkan Harga:" << endl;
    for (int i = 0; i < jumlahKamar; ++i) {
        displayKamar(kamar[i]);
    }
}

// mencari dengan metode sequential search
void searchKamarOrPenghuni(const string& query) {
    bool found = false;
    string lowerQuery = query;
    
    // Konversi query ke huruf kecil untuk pencarian tidak peka huruf besar/kecil
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& kamar : kamars) {
        // Konversi nomor kamar ke string dan pemilik ke huruf kecil
        string lowerPemilik = kamar.pemilik;
        transform(lowerPemilik.begin(), lowerPemilik.end(), lowerPemilik.begin(), ::tolower);

        // Bandingkan nomor kamar atau nama penghuni yang sesuai dengan query
        if (to_string(kamar.nomorKamar) == lowerQuery || lowerPemilik.find(lowerQuery) != string::npos) {
            found = true;
            displayKamar(kamar);
        }
    }

    if (!found) {
        cout << "Tidak ada kamar atau penghuni yang sesuai dengan pencarian Anda." << endl;
    }
}

// Fungsi untuk menampilkan menu admin
void MenuAdmin() {
    int pilihan;
    string query;

    cout << "================= Menu Admin ================" << endl;
    cout << "| 1. Tambah Kamar                           |" << endl;
    cout << "| 2. Hapus Kamar                            |" << endl;
    cout << "| 3. Update Status Kamar                    |" << endl;
    cout << "| 4. Sorting harga Kamar                    |" << endl;
    cout << "| 5. Pencarian No Kamar atau Nama Penghuni  |" << endl;
    cout << "| 6. Lihat Daftar Kamar                     |" << endl;
    cout << "| 7. Keluar                                 |" << endl;
    cout << "=============================================" << endl;
    cout << "Pilih Menu: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            registerRoom(kamars, sizeof(kamars) / sizeof(kamars[0]));
            MenuAdmin();
            break;
        case 2:
            deleteRoom(kamars, sizeof(kamars) / sizeof(kamars[0]));
            MenuAdmin();
            break;
        case 3:
            updateRoomStatus(kamars, sizeof(kamars) / sizeof(kamars[0]));
            MenuAdmin();
            break;            
        case 4:
            sortKamarByPrice(kamars, sizeof(kamars) / sizeof(kamars[0]));
            MenuAdmin();          
            break;
        case 5:
            cout << "Masukkan nomor kamar atau nama penghuni yang ingin dicari: ";
            cin >> query;
            searchKamarOrPenghuni(query);
            MenuAdmin();
            break;
        case 6:
            displayAllKamar();
            MenuAdmin();
            break;
        case 7:
            cout << "Anda telah keluar dari menu admin" << endl;
            break;
        default:
            cout << "Pilihan anda tidak valid, Silakan masukkan pilihan dengan benar" << endl;
            MenuAdmin();
            break;
    }
}

void registerUser() {
    UserData newUser;

    cout << "Masukkan Nama Pengguna: ";
    cin >> newUser.username;

    cout << "Masukkan Kata Sandi: ";
    cin >> newUser.password;

    cout << "Masukkan Nama Lengkap: ";
    cin.ignore(); // Membersihkan newline character dari buffer
    getline(cin, newUser.name);

    cout << "Masukkan Nomor Telepon: ";
    getline(cin, newUser.phoneNum);

    // Simpan informasi pengguna ke dalam file
    ofstream outFile("user_data.txt", ios::app); // Mode ios::app untuk menambahkan ke akhir file
    if (outFile.is_open()) {
        outFile << newUser.username << " " << newUser.password << " " << newUser.name << " " << newUser.phoneNum << endl;
        outFile.close();
        cout << "Registrasi Berhasil!" << endl;
    } else {
        cout << "Gagal membuka file untuk menyimpan data." << endl;
    }
}

void loginUser() {
    int loginAttempt = 0;
    string username, password;
    while (loginAttempt <= 3) {
        cout << "Masukkan Username Kamu: ";
        cin >> username;
        cout << "Masukkan Password kamu: ";
        cin >> password;

        ifstream inFile("user_data.txt");
        if (!inFile.is_open()) {
            cout << "Gagal membuka file data pengguna." << endl;
            return;
        }

        string line;
        bool loginSuccess = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData user;
            ss >> user.username >> user.password >> user.name >> user.phoneNum;

            if (username == user.username && password == user.password) {
                cout << "Anda Berhasil Sebagai Pengguna! Selamat datang, " << user.name << "." << endl;
                loginSuccess = true;
                MenuUser(username);
                break;
            }
        }

        inFile.close();

        if (loginSuccess) {
            return;
        } else {
            cout << "Username atau Password salah. Silakan coba lagi." << endl;
            loginAttempt++;
        }
    }

    cout << "Anda telah mencoba login sebanyak 3 kali. Silakan coba lagi nanti." << endl;
}

void loginAdmin() {
    int loginAttempt = 0;
    string username, password;

    while (loginAttempt <= 3) {
        cout << "Masukkan Username admin: ";
        cin >> username;
        cout << "Masukkan Password admin: ";
        cin >> password;

        ifstream inFile("admin_data.txt");
        if (!inFile.is_open()) {
            cout << "Gagal membuka file data admin." << endl;
            return;
        }

        string line;
        bool loginSuccess = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData admin;
            ss >> admin.username >> admin.password;

            if (username == admin.username && password == admin.password) {
                cout << "Anda Telah Berhasil login sebagai Admin!" << endl;
                cout << "--------------------------------------------" << endl;
                cout << ":::   SELAMAT DATANG DI KOS MELATI JAYA  :::" << endl;
                cout << "--------------------------------------------" << endl;
                loginSuccess = true;
                MenuAdmin();
                break;
            }
        }

        inFile.close();

        if (loginSuccess) {
            return;
        } else {
            cout << "Username atau Password salah. Silakan coba lagi." << endl;
            loginAttempt++;
        }
    }

    cout << "Anda telah mencoba login sebanyak 3 kali. Silakan coba lagi nanti." << endl;
}

int main() 
{
    loadStatusFromFile(kamars, sizeof(kamars) / sizeof(kamars[0]));
    char choice;
    
    do {
        cout << "--------------------------------------------" << endl;
        cout << ":::   SELAMAT DATANG DI KOS MELATI JAYA  :::" << endl;
        cout << "--------------------------------------------" << endl;

        cout << "|===========================================|" << endl;
        cout << "|------------- KOS MELATI JAYA -------------|" << endl;
        cout << "|===========================================|" << endl;
        cout << "|[1] Register                               |" << endl;
        cout << "|[2] Login as Admin                         |" << endl;
        cout << "|[3] Login as User                          |" << endl;
        cout << "|[4] Keluar                                 |" << endl;
        cout << "|===========================================|" << endl;

        cout << "Pilih Menu: ";
        cin >> choice;

        switch (choice) {
            case '1':
                registerUser();
                break;
            case '2':
                loginAdmin();
                break;
            case '3':
                loginUser();
                break;
            case '4':
                 cout << "Program ini telah berhenti, Terima Kasih" << endl;
                return 0; // Program akan berhenti dan keluar dari fungsi main
            default:
                cout << "Pilihan anda tidak valid, Silakan masukkan pilihan dengan benar" << endl;
        }
     } while (choice != '4'); 
    return 0;
}