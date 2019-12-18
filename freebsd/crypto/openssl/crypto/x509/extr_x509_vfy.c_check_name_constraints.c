#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int error; TYPE_1__* param; int /*<<< orphan*/  chain; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_15__ {int ex_flags; int /*<<< orphan*/ * nc; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_13__ {int hostflags; } ;
typedef  int /*<<< orphan*/  NAME_CONSTRAINTS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EXFLAG_PROXY ; 
 int EXFLAG_SI ; 
 int /*<<< orphan*/  GEN_DNS ; 
 int NAME_CONSTRAINTS_check (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int NAME_CONSTRAINTS_check_CN (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int NID_commonName ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int X509_CHECK_FLAG_ALWAYS_CHECK_SUBJECT ; 
 int X509_CHECK_FLAG_NEVER_CHECK_SUBJECT ; 
 int /*<<< orphan*/  X509_F_CHECK_NAME_CONSTRAINTS ; 
 int /*<<< orphan*/  X509_NAME_ENTRY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_ENTRY_get_object (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_NAME_ENTRY_set (int /*<<< orphan*/ ) ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_delete_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * X509_NAME_dup (int /*<<< orphan*/ *) ; 
 int X509_NAME_entry_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
#define  X509_V_ERR_OUT_OF_MEM 129 
 int X509_V_ERR_PROXY_SUBJECT_NAME_VIOLATION ; 
#define  X509_V_OK 128 
 int /*<<< orphan*/ * X509_get_issuer_name (TYPE_3__*) ; 
 int /*<<< orphan*/ * X509_get_subject_name (TYPE_3__*) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_san_id (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_X509_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify_cb_cert (TYPE_2__*,TYPE_3__*,int,int) ; 

__attribute__((used)) static int check_name_constraints(X509_STORE_CTX *ctx)
{
    int i;

    /* Check name constraints for all certificates */
    for (i = sk_X509_num(ctx->chain) - 1; i >= 0; i--) {
        X509 *x = sk_X509_value(ctx->chain, i);
        int j;

        /* Ignore self issued certs unless last in chain */
        if (i && (x->ex_flags & EXFLAG_SI))
            continue;

        /*
         * Proxy certificates policy has an extra constraint, where the
         * certificate subject MUST be the issuer with a single CN entry
         * added.
         * (RFC 3820: 3.4, 4.1.3 (a)(4))
         */
        if (x->ex_flags & EXFLAG_PROXY) {
            X509_NAME *tmpsubject = X509_get_subject_name(x);
            X509_NAME *tmpissuer = X509_get_issuer_name(x);
            X509_NAME_ENTRY *tmpentry = NULL;
            int last_object_nid = 0;
            int err = X509_V_OK;
            int last_object_loc = X509_NAME_entry_count(tmpsubject) - 1;

            /* Check that there are at least two RDNs */
            if (last_object_loc < 1) {
                err = X509_V_ERR_PROXY_SUBJECT_NAME_VIOLATION;
                goto proxy_name_done;
            }

            /*
             * Check that there is exactly one more RDN in subject as
             * there is in issuer.
             */
            if (X509_NAME_entry_count(tmpsubject)
                != X509_NAME_entry_count(tmpissuer) + 1) {
                err = X509_V_ERR_PROXY_SUBJECT_NAME_VIOLATION;
                goto proxy_name_done;
            }

            /*
             * Check that the last subject component isn't part of a
             * multivalued RDN
             */
            if (X509_NAME_ENTRY_set(X509_NAME_get_entry(tmpsubject,
                                                        last_object_loc))
                == X509_NAME_ENTRY_set(X509_NAME_get_entry(tmpsubject,
                                                           last_object_loc - 1))) {
                err = X509_V_ERR_PROXY_SUBJECT_NAME_VIOLATION;
                goto proxy_name_done;
            }

            /*
             * Check that the last subject RDN is a commonName, and that
             * all the previous RDNs match the issuer exactly
             */
            tmpsubject = X509_NAME_dup(tmpsubject);
            if (tmpsubject == NULL) {
                X509err(X509_F_CHECK_NAME_CONSTRAINTS, ERR_R_MALLOC_FAILURE);
                ctx->error = X509_V_ERR_OUT_OF_MEM;
                return 0;
            }

            tmpentry =
                X509_NAME_delete_entry(tmpsubject, last_object_loc);
            last_object_nid =
                OBJ_obj2nid(X509_NAME_ENTRY_get_object(tmpentry));

            if (last_object_nid != NID_commonName
                || X509_NAME_cmp(tmpsubject, tmpissuer) != 0) {
                err = X509_V_ERR_PROXY_SUBJECT_NAME_VIOLATION;
            }

            X509_NAME_ENTRY_free(tmpentry);
            X509_NAME_free(tmpsubject);

         proxy_name_done:
            if (err != X509_V_OK
                && !verify_cb_cert(ctx, x, i, err))
                return 0;
        }

        /*
         * Check against constraints for all certificates higher in chain
         * including trust anchor. Trust anchor not strictly speaking needed
         * but if it includes constraints it is to be assumed it expects them
         * to be obeyed.
         */
        for (j = sk_X509_num(ctx->chain) - 1; j > i; j--) {
            NAME_CONSTRAINTS *nc = sk_X509_value(ctx->chain, j)->nc;

            if (nc) {
                int rv = NAME_CONSTRAINTS_check(x, nc);

                /* If EE certificate check commonName too */
                if (rv == X509_V_OK && i == 0
                    && (ctx->param->hostflags
                        & X509_CHECK_FLAG_NEVER_CHECK_SUBJECT) == 0
                    && ((ctx->param->hostflags
                         & X509_CHECK_FLAG_ALWAYS_CHECK_SUBJECT) != 0
                        || !has_san_id(x, GEN_DNS)))
                    rv = NAME_CONSTRAINTS_check_CN(x, nc);

                switch (rv) {
                case X509_V_OK:
                    break;
                case X509_V_ERR_OUT_OF_MEM:
                    return 0;
                default:
                    if (!verify_cb_cert(ctx, x, i, rv))
                        return 0;
                    break;
                }
            }
        }
    }
    return 1;
}