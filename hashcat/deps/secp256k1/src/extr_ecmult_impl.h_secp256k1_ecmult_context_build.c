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
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge_storage ;
struct TYPE_3__ {int /*<<< orphan*/ ** pre_g_128; int /*<<< orphan*/ ** pre_g; } ;
typedef  TYPE_1__ secp256k1_ecmult_context ;

/* Variables and functions */
 int ECMULT_TABLE_SIZE (int /*<<< orphan*/ ) ; 
 size_t SECP256K1_ECMULT_CONTEXT_PREALLOCATED_SIZE ; 
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int /*<<< orphan*/  WINDOW_G ; 
 scalar_t__ manual_alloc (void**,int,void* const,size_t const) ; 
 int /*<<< orphan*/  secp256k1_ecmult_odd_multiples_table_storage_var (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_gej_double_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void secp256k1_ecmult_context_build(secp256k1_ecmult_context *ctx, void **prealloc) {
    secp256k1_gej gj;
    void* const base = *prealloc;
    size_t const prealloc_size = SECP256K1_ECMULT_CONTEXT_PREALLOCATED_SIZE;

    if (ctx->pre_g != NULL) {
        return;
    }

    /* get the generator */
    secp256k1_gej_set_ge(&gj, &secp256k1_ge_const_g);

    {
        size_t size = sizeof((*ctx->pre_g)[0]) * ((size_t)ECMULT_TABLE_SIZE(WINDOW_G));
        /* check for overflow */
        VERIFY_CHECK(size / sizeof((*ctx->pre_g)[0]) == ((size_t)ECMULT_TABLE_SIZE(WINDOW_G)));
        ctx->pre_g = (secp256k1_ge_storage (*)[])manual_alloc(prealloc, sizeof((*ctx->pre_g)[0]) * ECMULT_TABLE_SIZE(WINDOW_G), base, prealloc_size);
    }

    /* precompute the tables with odd multiples */
    secp256k1_ecmult_odd_multiples_table_storage_var(ECMULT_TABLE_SIZE(WINDOW_G), *ctx->pre_g, &gj);

#ifdef USE_ENDOMORPHISM
    {
        secp256k1_gej g_128j;
        int i;

        size_t size = sizeof((*ctx->pre_g_128)[0]) * ((size_t) ECMULT_TABLE_SIZE(WINDOW_G));
        /* check for overflow */
        VERIFY_CHECK(size / sizeof((*ctx->pre_g_128)[0]) == ((size_t)ECMULT_TABLE_SIZE(WINDOW_G)));
        ctx->pre_g_128 = (secp256k1_ge_storage (*)[])manual_alloc(prealloc, sizeof((*ctx->pre_g_128)[0]) * ECMULT_TABLE_SIZE(WINDOW_G), base, prealloc_size);

        /* calculate 2^128*generator */
        g_128j = gj;
        for (i = 0; i < 128; i++) {
            secp256k1_gej_double_var(&g_128j, &g_128j, NULL);
        }
        secp256k1_ecmult_odd_multiples_table_storage_var(ECMULT_TABLE_SIZE(WINDOW_G), *ctx->pre_g_128, &g_128j);
    }
#endif
}