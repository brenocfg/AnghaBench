#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ (* check_issued ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_3__* ctx; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_18__ {int /*<<< orphan*/  objs; } ;
typedef  TYPE_3__ X509_STORE ;
struct TYPE_16__ {int /*<<< orphan*/ * x509; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_1__ data; } ;
typedef  TYPE_4__ X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 scalar_t__ X509_LU_X509 ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_OBJECT_free (TYPE_4__*) ; 
 int X509_OBJECT_idx_by_subject (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_4__* X509_OBJECT_new () ; 
 int X509_STORE_CTX_get_by_subject (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  X509_STORE_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  X509_STORE_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/ * X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int sk_X509_OBJECT_num (int /*<<< orphan*/ ) ; 
 TYPE_4__* sk_X509_OBJECT_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ x509_check_cert_time (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

int X509_STORE_CTX_get1_issuer(X509 **issuer, X509_STORE_CTX *ctx, X509 *x)
{
    X509_NAME *xn;
    X509_OBJECT *obj = X509_OBJECT_new(), *pobj = NULL;
    X509_STORE *store = ctx->ctx;
    int i, ok, idx, ret;

    if (obj == NULL)
        return -1;
    *issuer = NULL;
    xn = X509_get_issuer_name(x);
    ok = X509_STORE_CTX_get_by_subject(ctx, X509_LU_X509, xn, obj);
    if (ok != 1) {
        X509_OBJECT_free(obj);
        return 0;
    }
    /* If certificate matches all OK */
    if (ctx->check_issued(ctx, x, obj->data.x509)) {
        if (x509_check_cert_time(ctx, obj->data.x509, -1)) {
            *issuer = obj->data.x509;
            if (!X509_up_ref(*issuer)) {
                *issuer = NULL;
                ok = -1;
            }
            X509_OBJECT_free(obj);
            return ok;
        }
    }
    X509_OBJECT_free(obj);

    if (store == NULL)
        return 0;

    /* Else find index of first cert accepted by 'check_issued' */
    ret = 0;
    X509_STORE_lock(store);
    idx = X509_OBJECT_idx_by_subject(store->objs, X509_LU_X509, xn);
    if (idx != -1) {            /* should be true as we've had at least one
                                 * match */
        /* Look through all matching certs for suitable issuer */
        for (i = idx; i < sk_X509_OBJECT_num(store->objs); i++) {
            pobj = sk_X509_OBJECT_value(store->objs, i);
            /* See if we've run past the matches */
            if (pobj->type != X509_LU_X509)
                break;
            if (X509_NAME_cmp(xn, X509_get_subject_name(pobj->data.x509)))
                break;
            if (ctx->check_issued(ctx, x, pobj->data.x509)) {
                *issuer = pobj->data.x509;
                ret = 1;
                /*
                 * If times check, exit with match,
                 * otherwise keep looking. Leave last
                 * match in issuer so we return nearest
                 * match if no certificate time is OK.
                 */

                if (x509_check_cert_time(ctx, *issuer, -1))
                    break;
            }
        }
    }
    if (*issuer && !X509_up_ref(*issuer)) {
        *issuer = NULL;
        ret = -1;
    }
    X509_STORE_unlock(store);
    return ret;
}