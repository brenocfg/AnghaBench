#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct kerneldumpkey {int kdk_encryptedkeysize; int kdk_encryption; int /*<<< orphan*/ * kdk_iv; int /*<<< orphan*/  kdk_encryptedkey; } ;
typedef  scalar_t__ ssize_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_DecryptFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DecryptUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * EVP_aes_256_cbc () ; 
 int /*<<< orphan*/ * EVP_chacha20 () ; 
 int KERNELDUMP_BUFFER_SIZE ; 
#define  KERNELDUMP_ENC_AES_256_CBC 129 
#define  KERNELDUMP_ENC_CHACHA20 128 
 int KERNELDUMP_KEY_MAX_SIZE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/ * PEM_read_RSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int RSA_private_decrypt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 
 scalar_t__ caph_enter () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pjdlog_error (char*,...) ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,int) ; 
 struct kerneldumpkey* read_key (int) ; 
 scalar_t__ wait_for_process (int) ; 
 int write (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
decrypt(int ofd, const char *privkeyfile, const char *keyfile,
    const char *input)
{
	uint8_t buf[KERNELDUMP_BUFFER_SIZE], key[KERNELDUMP_KEY_MAX_SIZE],
	    chachaiv[4 * 4];
	EVP_CIPHER_CTX *ctx;
	const EVP_CIPHER *cipher;
	FILE *fp;
	struct kerneldumpkey *kdk;
	RSA *privkey;
	int ifd, kfd, olen, privkeysize;
	ssize_t bytes;
	pid_t pid;

	PJDLOG_ASSERT(ofd >= 0);
	PJDLOG_ASSERT(privkeyfile != NULL);
	PJDLOG_ASSERT(keyfile != NULL);
	PJDLOG_ASSERT(input != NULL);

	ctx = NULL;
	privkey = NULL;

	/*
	 * Decrypt a core dump in a child process so we can unlink a partially
	 * decrypted core if the child process fails.
	 */
	pid = fork();
	if (pid == -1) {
		pjdlog_errno(LOG_ERR, "Unable to create child process");
		close(ofd);
		return (false);
	}

	if (pid > 0) {
		close(ofd);
		return (wait_for_process(pid) == 0);
	}

	kfd = open(keyfile, O_RDONLY);
	if (kfd == -1) {
		pjdlog_errno(LOG_ERR, "Unable to open %s", keyfile);
		goto failed;
	}
	ifd = open(input, O_RDONLY);
	if (ifd == -1) {
		pjdlog_errno(LOG_ERR, "Unable to open %s", input);
		goto failed;
	}
	fp = fopen(privkeyfile, "r");
	if (fp == NULL) {
		pjdlog_errno(LOG_ERR, "Unable to open %s", privkeyfile);
		goto failed;
	}

	if (caph_enter() < 0) {
		pjdlog_errno(LOG_ERR, "Unable to enter capability mode");
		goto failed;
	}

	privkey = RSA_new();
	if (privkey == NULL) {
		pjdlog_error("Unable to allocate an RSA structure: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		goto failed;
	}
	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL)
		goto failed;

	kdk = read_key(kfd);
	close(kfd);
	if (kdk == NULL)
		goto failed;

	privkey = PEM_read_RSAPrivateKey(fp, &privkey, NULL, NULL);
	fclose(fp);
	if (privkey == NULL) {
		pjdlog_error("Unable to read data from %s.", privkeyfile);
		goto failed;
	}

	privkeysize = RSA_size(privkey);
	if (privkeysize != (int)kdk->kdk_encryptedkeysize) {
		pjdlog_error("RSA modulus size mismatch: equals %db and should be %ub.",
		    8 * privkeysize, 8 * kdk->kdk_encryptedkeysize);
		goto failed;
	}

	switch (kdk->kdk_encryption) {
	case KERNELDUMP_ENC_AES_256_CBC:
		cipher = EVP_aes_256_cbc();
		break;
	case KERNELDUMP_ENC_CHACHA20:
		cipher = EVP_chacha20();
		break;
	default:
		pjdlog_error("Invalid encryption algorithm.");
		goto failed;
	}

	if (RSA_private_decrypt(kdk->kdk_encryptedkeysize,
	    kdk->kdk_encryptedkey, key, privkey,
	    RSA_PKCS1_PADDING) != sizeof(key)) {
		pjdlog_error("Unable to decrypt key: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		goto failed;
	}
	RSA_free(privkey);
	privkey = NULL;

	if (kdk->kdk_encryption == KERNELDUMP_ENC_CHACHA20) {
		/*
		 * OpenSSL treats the IV as 4 little-endian 32 bit integers.
		 *
		 * The first two represent a 64-bit counter, where the low half
		 * is the first 32-bit word.
		 *
		 * Start at counter block zero...
		 */
		memset(chachaiv, 0, 4 * 2);
		/*
		 * And use the IV specified by the dump.
		 */
		memcpy(&chachaiv[4 * 2], kdk->kdk_iv, 4 * 2);
		EVP_DecryptInit_ex(ctx, cipher, NULL, key, chachaiv);
	} else
		EVP_DecryptInit_ex(ctx, cipher, NULL, key, kdk->kdk_iv);
	EVP_CIPHER_CTX_set_padding(ctx, 0);

	explicit_bzero(key, sizeof(key));

	do {
		bytes = read(ifd, buf, sizeof(buf));
		if (bytes < 0) {
			pjdlog_errno(LOG_ERR, "Unable to read data from %s",
			    input);
			goto failed;
		}

		if (bytes > 0) {
			if (EVP_DecryptUpdate(ctx, buf, &olen, buf,
			    bytes) == 0) {
				pjdlog_error("Unable to decrypt core.");
				goto failed;
			}
		} else {
			if (EVP_DecryptFinal_ex(ctx, buf, &olen) == 0) {
				pjdlog_error("Unable to decrypt core.");
				goto failed;
			}
		}

		if (olen > 0 && write(ofd, buf, olen) != olen) {
			pjdlog_errno(LOG_ERR, "Unable to write core");
			goto failed;
		}
	} while (bytes > 0);

	explicit_bzero(buf, sizeof(buf));
	EVP_CIPHER_CTX_free(ctx);
	exit(0);
failed:
	explicit_bzero(key, sizeof(key));
	explicit_bzero(buf, sizeof(buf));
	RSA_free(privkey);
	if (ctx != NULL)
		EVP_CIPHER_CTX_free(ctx);
	exit(1);
}