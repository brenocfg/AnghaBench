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
typedef  int /*<<< orphan*/  secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
struct TYPE_5__ {int /*<<< orphan*/  error_callback; int /*<<< orphan*/  ecmult_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;
struct TYPE_6__ {int /*<<< orphan*/ * pt; int /*<<< orphan*/ * sc; } ;
typedef  TYPE_2__ ecmult_multi_data ;

/* Variables and functions */
 int /*<<< orphan*/  ecmult_multi_callback ; 
 int /*<<< orphan*/  ge_equals_gej (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_multi_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * secp256k1_scratch_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_scratch_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_exhaustive_ecmult_multi(const secp256k1_context *ctx, const secp256k1_ge *group, int order) {
    int i, j, k, x, y;
    secp256k1_scratch *scratch = secp256k1_scratch_create(&ctx->error_callback, 4096);
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            for (k = 0; k < order; k++) {
                for (x = 0; x < order; x++) {
                    for (y = 0; y < order; y++) {
                        secp256k1_gej tmp;
                        secp256k1_scalar g_sc;
                        ecmult_multi_data data;

                        secp256k1_scalar_set_int(&data.sc[0], i);
                        secp256k1_scalar_set_int(&data.sc[1], j);
                        secp256k1_scalar_set_int(&g_sc, k);
                        data.pt[0] = group[x];
                        data.pt[1] = group[y];

                        secp256k1_ecmult_multi_var(&ctx->error_callback, &ctx->ecmult_ctx, scratch, &tmp, &g_sc, ecmult_multi_callback, &data, 2);
                        ge_equals_gej(&group[(i * x + j * y + k) % order], &tmp);
                    }
                }
            }
        }
    }
    secp256k1_scratch_destroy(&ctx->error_callback, scratch);
}