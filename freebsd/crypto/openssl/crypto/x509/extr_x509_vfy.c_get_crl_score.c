#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_14__ {int idp_flags; unsigned int idp_reasons; int flags; scalar_t__ base_crl_number; } ;
typedef  TYPE_3__ X509_CRL ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_12__ {int flags; } ;

/* Variables and functions */
 int CRL_SCORE_AKID ; 
 int CRL_SCORE_ISSUER_NAME ; 
 int CRL_SCORE_NOCRITICAL ; 
 int CRL_SCORE_SCOPE ; 
 int CRL_SCORE_TIME ; 
 int EXFLAG_CRITICAL ; 
 int IDP_INDIRECT ; 
 int IDP_INVALID ; 
 int IDP_REASONS ; 
 int /*<<< orphan*/  X509_CRL_get_issuer (TYPE_3__*) ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_V_FLAG_EXTENDED_CRL_SUPPORT ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 scalar_t__ check_crl_time (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crl_akid_check (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ crl_crldp_check (int /*<<< orphan*/ *,TYPE_3__*,int,unsigned int*) ; 

__attribute__((used)) static int get_crl_score(X509_STORE_CTX *ctx, X509 **pissuer,
                         unsigned int *preasons, X509_CRL *crl, X509 *x)
{

    int crl_score = 0;
    unsigned int tmp_reasons = *preasons, crl_reasons;

    /* First see if we can reject CRL straight away */

    /* Invalid IDP cannot be processed */
    if (crl->idp_flags & IDP_INVALID)
        return 0;
    /* Reason codes or indirect CRLs need extended CRL support */
    if (!(ctx->param->flags & X509_V_FLAG_EXTENDED_CRL_SUPPORT)) {
        if (crl->idp_flags & (IDP_INDIRECT | IDP_REASONS))
            return 0;
    } else if (crl->idp_flags & IDP_REASONS) {
        /* If no new reasons reject */
        if (!(crl->idp_reasons & ~tmp_reasons))
            return 0;
    }
    /* Don't process deltas at this stage */
    else if (crl->base_crl_number)
        return 0;
    /* If issuer name doesn't match certificate need indirect CRL */
    if (X509_NAME_cmp(X509_get_issuer_name(x), X509_CRL_get_issuer(crl))) {
        if (!(crl->idp_flags & IDP_INDIRECT))
            return 0;
    } else
        crl_score |= CRL_SCORE_ISSUER_NAME;

    if (!(crl->flags & EXFLAG_CRITICAL))
        crl_score |= CRL_SCORE_NOCRITICAL;

    /* Check expiry */
    if (check_crl_time(ctx, crl, 0))
        crl_score |= CRL_SCORE_TIME;

    /* Check authority key ID and locate certificate issuer */
    crl_akid_check(ctx, crl, pissuer, &crl_score);

    /* If we can't locate certificate issuer at this point forget it */

    if (!(crl_score & CRL_SCORE_AKID))
        return 0;

    /* Check cert for matching CRL distribution points */

    if (crl_crldp_check(x, crl, crl_score, &crl_reasons)) {
        /* If no new reasons reject */
        if (!(crl_reasons & ~tmp_reasons))
            return 0;
        tmp_reasons |= crl_reasons;
        crl_score |= CRL_SCORE_SCOPE;
    }

    *preasons = tmp_reasons;

    return crl_score;

}