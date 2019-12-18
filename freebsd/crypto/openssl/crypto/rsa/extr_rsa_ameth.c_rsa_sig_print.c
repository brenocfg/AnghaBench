#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  RSA_PSS_PARAMS ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;

/* Variables and functions */
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_PSS_PARAMS_free (int /*<<< orphan*/ *) ; 
 int X509_signature_dump (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * rsa_pss_decode (TYPE_1__ const*) ; 
 int rsa_pss_param_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rsa_sig_print(BIO *bp, const X509_ALGOR *sigalg,
                         const ASN1_STRING *sig, int indent, ASN1_PCTX *pctx)
{
    if (OBJ_obj2nid(sigalg->algorithm) == EVP_PKEY_RSA_PSS) {
        int rv;
        RSA_PSS_PARAMS *pss = rsa_pss_decode(sigalg);

        rv = rsa_pss_param_print(bp, 0, pss, indent);
        RSA_PSS_PARAMS_free(pss);
        if (!rv)
            return 0;
    } else if (!sig && BIO_puts(bp, "\n") <= 0) {
        return 0;
    }
    if (sig)
        return X509_signature_dump(bp, sig, indent);
    return 1;
}