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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_Parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int init_keygen_file(EVP_PKEY_CTX **pctx, const char *file, ENGINE *e)
{
    BIO *pbio;
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    if (*pctx) {
        BIO_puts(bio_err, "Parameters already set!\n");
        return 0;
    }

    pbio = BIO_new_file(file, "r");
    if (!pbio) {
        BIO_printf(bio_err, "Can't open parameter file %s\n", file);
        return 0;
    }

    pkey = PEM_read_bio_Parameters(pbio, NULL);
    BIO_free(pbio);

    if (!pkey) {
        BIO_printf(bio_err, "Error reading parameter file %s\n", file);
        return 0;
    }

    ctx = EVP_PKEY_CTX_new(pkey, e);
    if (ctx == NULL)
        goto err;
    if (EVP_PKEY_keygen_init(ctx) <= 0)
        goto err;
    EVP_PKEY_free(pkey);
    *pctx = ctx;
    return 1;

 err:
    BIO_puts(bio_err, "Error initializing context\n");
    ERR_print_errors(bio_err);
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return 0;

}