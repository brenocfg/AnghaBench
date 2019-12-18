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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_free_strings () ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/ * load_public_key_buf (unsigned char const*,int) ; 
 int /*<<< orphan*/ * load_public_key_file (char const*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sha256_fd (int,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static bool
rsa_verify_cert(int fd, const char *sigfile, const unsigned char *key,
    int keylen, unsigned char *sig, int siglen)
{
	EVP_MD_CTX *mdctx;
	EVP_PKEY *pkey;
	char sha256[(SHA256_DIGEST_LENGTH * 2) + 2];
	char errbuf[1024];
	bool ret;

	pkey = NULL;
	mdctx = NULL;
	ret = false;

	SSL_load_error_strings();

	/* Compute SHA256 of the package. */
	if (lseek(fd, 0, 0) == -1) {
		warn("lseek");
		goto cleanup;
	}
	if ((sha256_fd(fd, sha256)) == -1) {
		warnx("Error creating SHA256 hash for package");
		goto cleanup;
	}

	if (sigfile != NULL) {
		if ((pkey = load_public_key_file(sigfile)) == NULL) {
			warnx("Error reading public key");
			goto cleanup;
		}
	} else {
		if ((pkey = load_public_key_buf(key, keylen)) == NULL) {
			warnx("Error reading public key");
			goto cleanup;
		}
	}

	/* Verify signature of the SHA256(pkg) is valid. */
	if ((mdctx = EVP_MD_CTX_create()) == NULL) {
		warnx("%s", ERR_error_string(ERR_get_error(), errbuf));
		goto error;
	}

	if (EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pkey) != 1) {
		warnx("%s", ERR_error_string(ERR_get_error(), errbuf));
		goto error;
	}
	if (EVP_DigestVerifyUpdate(mdctx, sha256, strlen(sha256)) != 1) {
		warnx("%s", ERR_error_string(ERR_get_error(), errbuf));
		goto error;
	}

	if (EVP_DigestVerifyFinal(mdctx, sig, siglen) != 1) {
		warnx("%s", ERR_error_string(ERR_get_error(), errbuf));
		goto error;
	}

	ret = true;
	printf("done\n");
	goto cleanup;

error:
	printf("failed\n");

cleanup:
	if (pkey)
		EVP_PKEY_free(pkey);
	if (mdctx)
		EVP_MD_CTX_destroy(mdctx);
	ERR_free_strings();

	return (ret);
}