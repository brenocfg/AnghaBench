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
struct tls_data {int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_dup_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * PEM_read_bio_DHparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_DSAparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_CTX_set_tmp_dh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_global_dh(struct tls_data *data, const char *dh_file)
{
#ifdef OPENSSL_NO_DH
	if (dh_file == NULL)
		return 0;
	wpa_printf(MSG_ERROR, "TLS: openssl does not include DH support, but "
		   "dh_file specified");
	return -1;
#else /* OPENSSL_NO_DH */
	SSL_CTX *ssl_ctx = data->ssl;
	DH *dh;
	BIO *bio;

	/* TODO: add support for dh_blob */
	if (dh_file == NULL)
		return 0;
	if (ssl_ctx == NULL)
		return -1;

	bio = BIO_new_file(dh_file, "r");
	if (bio == NULL) {
		wpa_printf(MSG_INFO, "TLS: Failed to open DH file '%s': %s",
			   dh_file, ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}
	dh = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
	BIO_free(bio);
#ifndef OPENSSL_NO_DSA
	while (dh == NULL) {
		DSA *dsa;
		wpa_printf(MSG_DEBUG, "TLS: Failed to parse DH file '%s': %s -"
			   " trying to parse as DSA params", dh_file,
			   ERR_error_string(ERR_get_error(), NULL));
		bio = BIO_new_file(dh_file, "r");
		if (bio == NULL)
			break;
		dsa = PEM_read_bio_DSAparams(bio, NULL, NULL, NULL);
		BIO_free(bio);
		if (!dsa) {
			wpa_printf(MSG_DEBUG, "TLS: Failed to parse DSA file "
				   "'%s': %s", dh_file,
				   ERR_error_string(ERR_get_error(), NULL));
			break;
		}

		wpa_printf(MSG_DEBUG, "TLS: DH file in DSA param format");
		dh = DSA_dup_DH(dsa);
		DSA_free(dsa);
		if (dh == NULL) {
			wpa_printf(MSG_INFO, "TLS: Failed to convert DSA "
				   "params into DH params");
			break;
		}
		break;
	}
#endif /* !OPENSSL_NO_DSA */
	if (dh == NULL) {
		wpa_printf(MSG_INFO, "TLS: Failed to read/parse DH/DSA file "
			   "'%s'", dh_file);
		return -1;
	}

	if (SSL_CTX_set_tmp_dh(ssl_ctx, dh) != 1) {
		wpa_printf(MSG_INFO, "TLS: Failed to set DH params from '%s': "
			   "%s", dh_file,
			   ERR_error_string(ERR_get_error(), NULL));
		DH_free(dh);
		return -1;
	}
	DH_free(dh);
	return 0;
#endif /* OPENSSL_NO_DH */
}