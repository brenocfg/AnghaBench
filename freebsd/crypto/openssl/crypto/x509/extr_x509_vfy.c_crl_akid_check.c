#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int error_depth; int /*<<< orphan*/  untrusted; TYPE_1__* param; int /*<<< orphan*/  chain; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_9__ {int /*<<< orphan*/  akid; } ;
typedef  TYPE_3__ X509_CRL ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int CRL_SCORE_AKID ; 
 int CRL_SCORE_ISSUER_CERT ; 
 int CRL_SCORE_ISSUER_NAME ; 
 int CRL_SCORE_SAME_PATH ; 
 int /*<<< orphan*/ * X509_CRL_get_issuer (TYPE_3__*) ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int X509_V_FLAG_EXTENDED_CRL_SUPPORT ; 
 scalar_t__ X509_V_OK ; 
 scalar_t__ X509_check_akid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void crl_akid_check(X509_STORE_CTX *ctx, X509_CRL *crl,
                           X509 **pissuer, int *pcrl_score)
{
    X509 *crl_issuer = NULL;
    X509_NAME *cnm = X509_CRL_get_issuer(crl);
    int cidx = ctx->error_depth;
    int i;

    if (cidx != sk_X509_num(ctx->chain) - 1)
        cidx++;

    crl_issuer = sk_X509_value(ctx->chain, cidx);

    if (X509_check_akid(crl_issuer, crl->akid) == X509_V_OK) {
        if (*pcrl_score & CRL_SCORE_ISSUER_NAME) {
            *pcrl_score |= CRL_SCORE_AKID | CRL_SCORE_ISSUER_CERT;
            *pissuer = crl_issuer;
            return;
        }
    }

    for (cidx++; cidx < sk_X509_num(ctx->chain); cidx++) {
        crl_issuer = sk_X509_value(ctx->chain, cidx);
        if (X509_NAME_cmp(X509_get_subject_name(crl_issuer), cnm))
            continue;
        if (X509_check_akid(crl_issuer, crl->akid) == X509_V_OK) {
            *pcrl_score |= CRL_SCORE_AKID | CRL_SCORE_SAME_PATH;
            *pissuer = crl_issuer;
            return;
        }
    }

    /* Anything else needs extended CRL support */

    if (!(ctx->param->flags & X509_V_FLAG_EXTENDED_CRL_SUPPORT))
        return;

    /*
     * Otherwise the CRL issuer is not on the path. Look for it in the set of
     * untrusted certificates.
     */
    for (i = 0; i < sk_X509_num(ctx->untrusted); i++) {
        crl_issuer = sk_X509_value(ctx->untrusted, i);
        if (X509_NAME_cmp(X509_get_subject_name(crl_issuer), cnm))
            continue;
        if (X509_check_akid(crl_issuer, crl->akid) == X509_V_OK) {
            *pissuer = crl_issuer;
            *pcrl_score |= CRL_SCORE_AKID;
            return;
        }
    }
}