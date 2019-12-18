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
typedef  int /*<<< orphan*/  X509V3_CTX ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_EXT_add_nconf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509V3_set_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_set_nconf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_delete_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ X509_get_ext_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_issuer_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_set_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  set_cert_times (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sign(X509 *x, EVP_PKEY *pkey, int days, int clrext,
                const EVP_MD *digest, CONF *conf, const char *section,
                int preserve_dates)
{

    if (!X509_set_issuer_name(x, X509_get_subject_name(x)))
        goto err;
    if (!preserve_dates && !set_cert_times(x, NULL, NULL, days))
        goto err;
    if (!X509_set_pubkey(x, pkey))
        goto err;
    if (clrext) {
        while (X509_get_ext_count(x) > 0)
            X509_delete_ext(x, 0);
    }
    if (conf != NULL) {
        X509V3_CTX ctx;
        X509_set_version(x, 2); /* version 3 certificate */
        X509V3_set_ctx(&ctx, x, x, NULL, NULL, 0);
        X509V3_set_nconf(&ctx, conf);
        if (!X509V3_EXT_add_nconf(conf, &ctx, section, x))
            goto err;
    }
    if (!X509_sign(x, pkey, digest))
        goto err;
    return 1;
 err:
    ERR_print_errors(bio_err);
    return 0;
}