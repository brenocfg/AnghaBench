#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_8__ {int trust; } ;
typedef  TYPE_3__ X509_PURPOSE ;
struct TYPE_6__ {int purpose; int trust; } ;

/* Variables and functions */
 int /*<<< orphan*/  X509_F_X509_STORE_CTX_PURPOSE_INHERIT ; 
 TYPE_3__* X509_PURPOSE_get0 (int) ; 
 int X509_PURPOSE_get_by_id (int) ; 
 int /*<<< orphan*/  X509_R_UNKNOWN_PURPOSE_ID ; 
 int /*<<< orphan*/  X509_R_UNKNOWN_TRUST_ID ; 
 int X509_TRUST_DEFAULT ; 
 int X509_TRUST_get_by_id (int) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int X509_STORE_CTX_purpose_inherit(X509_STORE_CTX *ctx, int def_purpose,
                                   int purpose, int trust)
{
    int idx;
    /* If purpose not set use default */
    if (!purpose)
        purpose = def_purpose;
    /* If we have a purpose then check it is valid */
    if (purpose) {
        X509_PURPOSE *ptmp;
        idx = X509_PURPOSE_get_by_id(purpose);
        if (idx == -1) {
            X509err(X509_F_X509_STORE_CTX_PURPOSE_INHERIT,
                    X509_R_UNKNOWN_PURPOSE_ID);
            return 0;
        }
        ptmp = X509_PURPOSE_get0(idx);
        if (ptmp->trust == X509_TRUST_DEFAULT) {
            idx = X509_PURPOSE_get_by_id(def_purpose);
            /*
             * XXX: In the two callers above def_purpose is always 0, which is
             * not a known value, so idx will always be -1.  How is the
             * X509_TRUST_DEFAULT case actually supposed to be handled?
             */
            if (idx == -1) {
                X509err(X509_F_X509_STORE_CTX_PURPOSE_INHERIT,
                        X509_R_UNKNOWN_PURPOSE_ID);
                return 0;
            }
            ptmp = X509_PURPOSE_get0(idx);
        }
        /* If trust not set then get from purpose default */
        if (!trust)
            trust = ptmp->trust;
    }
    if (trust) {
        idx = X509_TRUST_get_by_id(trust);
        if (idx == -1) {
            X509err(X509_F_X509_STORE_CTX_PURPOSE_INHERIT,
                    X509_R_UNKNOWN_TRUST_ID);
            return 0;
        }
    }

    if (purpose && !ctx->param->purpose)
        ctx->param->purpose = purpose;
    if (trust && !ctx->param->trust)
        ctx->param->trust = trust;
    return 1;
}