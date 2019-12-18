#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_6__ {int current_crl_score; int /*<<< orphan*/ * current_crl; TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_CRL ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  check_time; } ;

/* Variables and functions */
 int CRL_SCORE_TIME_DELTA ; 
 scalar_t__ X509_CRL_get0_lastUpdate (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_CRL_get0_nextUpdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_V_ERR_CRL_HAS_EXPIRED ; 
 int /*<<< orphan*/  X509_V_ERR_CRL_NOT_YET_VALID ; 
 int /*<<< orphan*/  X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD ; 
 int /*<<< orphan*/  X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD ; 
 int X509_V_FLAG_NO_CHECK_TIME ; 
 int X509_V_FLAG_USE_CHECK_TIME ; 
 int X509_cmp_time (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_cb_crl (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_crl_time(X509_STORE_CTX *ctx, X509_CRL *crl, int notify)
{
    time_t *ptime;
    int i;

    if (notify)
        ctx->current_crl = crl;
    if (ctx->param->flags & X509_V_FLAG_USE_CHECK_TIME)
        ptime = &ctx->param->check_time;
    else if (ctx->param->flags & X509_V_FLAG_NO_CHECK_TIME)
        return 1;
    else
        ptime = NULL;

    i = X509_cmp_time(X509_CRL_get0_lastUpdate(crl), ptime);
    if (i == 0) {
        if (!notify)
            return 0;
        if (!verify_cb_crl(ctx, X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD))
            return 0;
    }

    if (i > 0) {
        if (!notify)
            return 0;
        if (!verify_cb_crl(ctx, X509_V_ERR_CRL_NOT_YET_VALID))
            return 0;
    }

    if (X509_CRL_get0_nextUpdate(crl)) {
        i = X509_cmp_time(X509_CRL_get0_nextUpdate(crl), ptime);

        if (i == 0) {
            if (!notify)
                return 0;
            if (!verify_cb_crl(ctx, X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD))
                return 0;
        }
        /* Ignore expiry of base CRL is delta is valid */
        if ((i < 0) && !(ctx->current_crl_score & CRL_SCORE_TIME_DELTA)) {
            if (!notify)
                return 0;
            if (!verify_cb_crl(ctx, X509_V_ERR_CRL_HAS_EXPIRED))
                return 0;
        }
    }

    if (notify)
        ctx->current_crl = NULL;

    return 1;
}