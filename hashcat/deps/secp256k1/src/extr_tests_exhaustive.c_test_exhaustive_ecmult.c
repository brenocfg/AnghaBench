#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
struct TYPE_3__ {int /*<<< orphan*/  ecmult_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  ge_equals_gej (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_const (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 

void test_exhaustive_ecmult(const secp256k1_context *ctx, const secp256k1_ge *group, const secp256k1_gej *groupj, int order) {
    int i, j, r_log;
    for (r_log = 1; r_log < order; r_log++) {
        for (j = 0; j < order; j++) {
            for (i = 0; i < order; i++) {
                secp256k1_gej tmp;
                secp256k1_scalar na, ng;
                secp256k1_scalar_set_int(&na, i);
                secp256k1_scalar_set_int(&ng, j);

                secp256k1_ecmult(&ctx->ecmult_ctx, &tmp, &groupj[r_log], &na, &ng);
                ge_equals_gej(&group[(i * r_log + j) % order], &tmp);

                if (i > 0) {
                    secp256k1_ecmult_const(&tmp, &group[i], &ng, 256);
                    ge_equals_gej(&group[(i * j) % order], &tmp);
                }
            }
        }
    }
}