#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * v; int /*<<< orphan*/ * s; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; int /*<<< orphan*/ * info; } ;
struct TYPE_5__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BUF_strdup (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

int SSL_set_srp_server_param(SSL *s, const BIGNUM *N, const BIGNUM *g,
                             BIGNUM *sa, BIGNUM *v, char *info)
{
    if (N != NULL) {
        if (s->srp_ctx.N != NULL) {
            if (!BN_copy(s->srp_ctx.N, N)) {
                BN_free(s->srp_ctx.N);
                s->srp_ctx.N = NULL;
            }
        } else
            s->srp_ctx.N = BN_dup(N);
    }
    if (g != NULL) {
        if (s->srp_ctx.g != NULL) {
            if (!BN_copy(s->srp_ctx.g, g)) {
                BN_free(s->srp_ctx.g);
                s->srp_ctx.g = NULL;
            }
        } else
            s->srp_ctx.g = BN_dup(g);
    }
    if (sa != NULL) {
        if (s->srp_ctx.s != NULL) {
            if (!BN_copy(s->srp_ctx.s, sa)) {
                BN_free(s->srp_ctx.s);
                s->srp_ctx.s = NULL;
            }
        } else
            s->srp_ctx.s = BN_dup(sa);
    }
    if (v != NULL) {
        if (s->srp_ctx.v != NULL) {
            if (!BN_copy(s->srp_ctx.v, v)) {
                BN_free(s->srp_ctx.v);
                s->srp_ctx.v = NULL;
            }
        } else
            s->srp_ctx.v = BN_dup(v);
    }
    if (info != NULL) {
        if (s->srp_ctx.info)
            OPENSSL_free(s->srp_ctx.info);
        if ((s->srp_ctx.info = BUF_strdup(info)) == NULL)
            return -1;
    }

    if (!(s->srp_ctx.N) ||
        !(s->srp_ctx.g) || !(s->srp_ctx.s) || !(s->srp_ctx.v))
        return -1;

    return 1;
}