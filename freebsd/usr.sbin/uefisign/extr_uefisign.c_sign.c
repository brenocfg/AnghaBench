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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 size_t BIO_get_mem_data (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (void*,size_t) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIGEST ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_pkcs9_contentType ; 
 int /*<<< orphan*/  OBJ_txt2obj (char*,int) ; 
 int PKCS7_BINARY ; 
 int PKCS7_PARTIAL ; 
 int /*<<< orphan*/  PKCS7_add_signed_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_print_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PKCS7_sign_add_signer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_OBJECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int i2d_PKCS7_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  magic (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  receive_chunk (void**,size_t*,int) ; 
 int /*<<< orphan*/  send_chunk (void*,size_t,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
sign(X509 *cert, EVP_PKEY *key, int pipefd)
{
	PKCS7 *pkcs7;
	BIO *bio, *out;
	const EVP_MD *md;
	PKCS7_SIGNER_INFO *info;
	void *digest, *signature;
	size_t digest_len, signature_len;
	int ok;

	assert(cert != NULL);
	assert(key != NULL);

	receive_chunk(&digest, &digest_len, pipefd);

	bio = BIO_new_mem_buf(digest, digest_len);
	if (bio == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "BIO_new_mem_buf(3) failed");
	}

	pkcs7 = PKCS7_sign(NULL, NULL, NULL, bio, PKCS7_BINARY | PKCS7_PARTIAL);
	if (pkcs7 == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "PKCS7_sign(3) failed");
	}

	md = EVP_get_digestbyname(DIGEST);
	if (md == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "EVP_get_digestbyname(\"%s\") failed", DIGEST);
	}

	info = PKCS7_sign_add_signer(pkcs7, cert, key, md, 0);
	if (info == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "PKCS7_sign_add_signer(3) failed");
	}

	/*
	 * XXX: All the signed binaries seem to have this, but where is it
	 *      described in the spec?
	 */
	PKCS7_add_signed_attribute(info, NID_pkcs9_contentType,
	    V_ASN1_OBJECT, OBJ_txt2obj("1.3.6.1.4.1.311.2.1.4", 1));

	magic(pkcs7, digest, digest_len);

#if 0
	out = BIO_new(BIO_s_file());
	BIO_set_fp(out, stdout, BIO_NOCLOSE);
	PKCS7_print_ctx(out, pkcs7, 0, NULL);

	i2d_PKCS7_bio(out, pkcs7);
#endif

	out = BIO_new(BIO_s_mem());
	if (out == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "BIO_new(3) failed");
	}

	ok = i2d_PKCS7_bio(out, pkcs7);
	if (ok == 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "i2d_PKCS7_bio(3) failed");
	}

	signature_len = BIO_get_mem_data(out, &signature);
	if (signature_len <= 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "BIO_get_mem_data(3) failed");
	}

	(void)BIO_set_close(out, BIO_NOCLOSE);
	BIO_free(out);

	send_chunk(signature, signature_len, pipefd);
}