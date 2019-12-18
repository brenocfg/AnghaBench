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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
#define  EVP_PKEY_OP_DECRYPT 137 
#define  EVP_PKEY_OP_DERIVE 136 
#define  EVP_PKEY_OP_ENCRYPT 135 
#define  EVP_PKEY_OP_SIGN 134 
#define  EVP_PKEY_OP_VERIFY 133 
#define  EVP_PKEY_OP_VERIFYRECOVER 132 
 int EVP_PKEY_decrypt_init (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_encrypt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_sign_init (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_verify_init (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_verify_recover_init (int /*<<< orphan*/ *) ; 
#define  KEY_CERT 131 
#define  KEY_NONE 130 
#define  KEY_PRIVKEY 129 
#define  KEY_PUBKEY 128 
 int NID_undef ; 
 int OBJ_ln2nid (char const*) ; 
 int OBJ_sn2nid (char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_passwd (char*,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * load_cert (char const*,int,char*) ; 
 int /*<<< orphan*/ * load_key (char const*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * load_pubkey (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static EVP_PKEY_CTX *init_ctx(const char *kdfalg, int *pkeysize,
                              const char *keyfile, int keyform, int key_type,
                              char *passinarg, int pkey_op, ENGINE *e,
                              const int engine_impl)
{
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    ENGINE *impl = NULL;
    char *passin = NULL;
    int rv = -1;
    X509 *x;
    if (((pkey_op == EVP_PKEY_OP_SIGN) || (pkey_op == EVP_PKEY_OP_DECRYPT)
         || (pkey_op == EVP_PKEY_OP_DERIVE))
        && (key_type != KEY_PRIVKEY && kdfalg == NULL)) {
        BIO_printf(bio_err, "A private key is needed for this operation\n");
        goto end;
    }
    if (!app_passwd(passinarg, NULL, &passin, NULL)) {
        BIO_printf(bio_err, "Error getting password\n");
        goto end;
    }
    switch (key_type) {
    case KEY_PRIVKEY:
        pkey = load_key(keyfile, keyform, 0, passin, e, "Private Key");
        break;

    case KEY_PUBKEY:
        pkey = load_pubkey(keyfile, keyform, 0, NULL, e, "Public Key");
        break;

    case KEY_CERT:
        x = load_cert(keyfile, keyform, "Certificate");
        if (x) {
            pkey = X509_get_pubkey(x);
            X509_free(x);
        }
        break;

    case KEY_NONE:
        break;

    }

#ifndef OPENSSL_NO_ENGINE
    if (engine_impl)
        impl = e;
#endif

    if (kdfalg != NULL) {
        int kdfnid = OBJ_sn2nid(kdfalg);

        if (kdfnid == NID_undef) {
            kdfnid = OBJ_ln2nid(kdfalg);
            if (kdfnid == NID_undef) {
                BIO_printf(bio_err, "The given KDF \"%s\" is unknown.\n",
                           kdfalg);
                goto end;
            }
        }
        ctx = EVP_PKEY_CTX_new_id(kdfnid, impl);
    } else {
        if (pkey == NULL)
            goto end;
        *pkeysize = EVP_PKEY_size(pkey);
        ctx = EVP_PKEY_CTX_new(pkey, impl);
        EVP_PKEY_free(pkey);
    }

    if (ctx == NULL)
        goto end;

    switch (pkey_op) {
    case EVP_PKEY_OP_SIGN:
        rv = EVP_PKEY_sign_init(ctx);
        break;

    case EVP_PKEY_OP_VERIFY:
        rv = EVP_PKEY_verify_init(ctx);
        break;

    case EVP_PKEY_OP_VERIFYRECOVER:
        rv = EVP_PKEY_verify_recover_init(ctx);
        break;

    case EVP_PKEY_OP_ENCRYPT:
        rv = EVP_PKEY_encrypt_init(ctx);
        break;

    case EVP_PKEY_OP_DECRYPT:
        rv = EVP_PKEY_decrypt_init(ctx);
        break;

    case EVP_PKEY_OP_DERIVE:
        rv = EVP_PKEY_derive_init(ctx);
        break;
    }

    if (rv <= 0) {
        EVP_PKEY_CTX_free(ctx);
        ctx = NULL;
    }

 end:
    OPENSSL_free(passin);
    return ctx;

}