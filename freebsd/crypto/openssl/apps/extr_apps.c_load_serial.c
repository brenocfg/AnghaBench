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
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  a2i_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  rand_serial (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BIGNUM *load_serial(const char *serialfile, int create, ASN1_INTEGER **retai)
{
    BIO *in = NULL;
    BIGNUM *ret = NULL;
    char buf[1024];
    ASN1_INTEGER *ai = NULL;

    ai = ASN1_INTEGER_new();
    if (ai == NULL)
        goto err;

    in = BIO_new_file(serialfile, "r");
    if (in == NULL) {
        if (!create) {
            perror(serialfile);
            goto err;
        }
        ERR_clear_error();
        ret = BN_new();
        if (ret == NULL || !rand_serial(ret, ai))
            BIO_printf(bio_err, "Out of memory\n");
    } else {
        if (!a2i_ASN1_INTEGER(in, ai, buf, 1024)) {
            BIO_printf(bio_err, "unable to load number from %s\n",
                       serialfile);
            goto err;
        }
        ret = ASN1_INTEGER_to_BN(ai, NULL);
        if (ret == NULL) {
            BIO_printf(bio_err,
                       "error converting number from bin to BIGNUM\n");
            goto err;
        }
    }

    if (ret && retai) {
        *retai = ai;
        ai = NULL;
    }
 err:
    BIO_free(in);
    ASN1_INTEGER_free(ai);
    return ret;
}