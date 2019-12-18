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
struct sshkey {int type; int ecdsa_nid; int /*<<< orphan*/ * ecdsa; int /*<<< orphan*/  dsa; int /*<<< orphan*/  rsa; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DSA_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_DSA ; 
 scalar_t__ EVP_PKEY_EC ; 
 scalar_t__ EVP_PKEY_RSA ; 
 scalar_t__ EVP_PKEY_base_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get1_DSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get1_RSA (int /*<<< orphan*/ *) ; 
 scalar_t__ INT_MAX ; 
 int KEY_DSA ; 
 int KEY_ECDSA ; 
 int KEY_RSA ; 
 int KEY_UNSPEC ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int RSA_blinding_on (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int check_rsa_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_libcrypto_errors () ; 
 int convert_libcrypto_error () ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/ * sshkey_curve_nid_to_name (int) ; 
 int /*<<< orphan*/  sshkey_dump_ec_key (int /*<<< orphan*/ *) ; 
 scalar_t__ sshkey_ec_validate_private (int /*<<< orphan*/ *) ; 
 scalar_t__ sshkey_ec_validate_public (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshkey_ecdsa_key_to_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 struct sshkey* sshkey_new (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
sshkey_parse_private_pem_fileblob(struct sshbuf *blob, int type,
    const char *passphrase, struct sshkey **keyp)
{
	EVP_PKEY *pk = NULL;
	struct sshkey *prv = NULL;
	BIO *bio = NULL;
	int r;

	if (keyp != NULL)
		*keyp = NULL;

	if ((bio = BIO_new(BIO_s_mem())) == NULL || sshbuf_len(blob) > INT_MAX)
		return SSH_ERR_ALLOC_FAIL;
	if (BIO_write(bio, sshbuf_ptr(blob), sshbuf_len(blob)) !=
	    (int)sshbuf_len(blob)) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}

	clear_libcrypto_errors();
	if ((pk = PEM_read_bio_PrivateKey(bio, NULL, NULL,
	    (char *)passphrase)) == NULL) {
		r = convert_libcrypto_error();
		goto out;
	}
	if (EVP_PKEY_base_id(pk) == EVP_PKEY_RSA &&
	    (type == KEY_UNSPEC || type == KEY_RSA)) {
		if ((prv = sshkey_new(KEY_UNSPEC)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		prv->rsa = EVP_PKEY_get1_RSA(pk);
		prv->type = KEY_RSA;
#ifdef DEBUG_PK
		RSA_print_fp(stderr, prv->rsa, 8);
#endif
		if (RSA_blinding_on(prv->rsa, NULL) != 1) {
			r = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		if ((r = check_rsa_length(prv->rsa)) != 0)
			goto out;
	} else if (EVP_PKEY_base_id(pk) == EVP_PKEY_DSA &&
	    (type == KEY_UNSPEC || type == KEY_DSA)) {
		if ((prv = sshkey_new(KEY_UNSPEC)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		prv->dsa = EVP_PKEY_get1_DSA(pk);
		prv->type = KEY_DSA;
#ifdef DEBUG_PK
		DSA_print_fp(stderr, prv->dsa, 8);
#endif
#ifdef OPENSSL_HAS_ECC
	} else if (EVP_PKEY_base_id(pk) == EVP_PKEY_EC &&
	    (type == KEY_UNSPEC || type == KEY_ECDSA)) {
		if ((prv = sshkey_new(KEY_UNSPEC)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		prv->ecdsa = EVP_PKEY_get1_EC_KEY(pk);
		prv->type = KEY_ECDSA;
		prv->ecdsa_nid = sshkey_ecdsa_key_to_nid(prv->ecdsa);
		if (prv->ecdsa_nid == -1 ||
		    sshkey_curve_nid_to_name(prv->ecdsa_nid) == NULL ||
		    sshkey_ec_validate_public(EC_KEY_get0_group(prv->ecdsa),
		    EC_KEY_get0_public_key(prv->ecdsa)) != 0 ||
		    sshkey_ec_validate_private(prv->ecdsa) != 0) {
			r = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
# ifdef DEBUG_PK
		if (prv != NULL && prv->ecdsa != NULL)
			sshkey_dump_ec_key(prv->ecdsa);
# endif
#endif /* OPENSSL_HAS_ECC */
	} else {
		r = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	r = 0;
	if (keyp != NULL) {
		*keyp = prv;
		prv = NULL;
	}
 out:
	BIO_free(bio);
	EVP_PKEY_free(pk);
	sshkey_free(prv);
	return r;
}