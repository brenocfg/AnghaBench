#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge_storage ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;
struct TYPE_4__ {int /*<<< orphan*/ *** prec; } ;
typedef  TYPE_1__ secp256k1_ecmult_gen_context ;

/* Variables and functions */
 int ECMULT_GEN_PREC_B ; 
 int ECMULT_GEN_PREC_G ; 
 int ECMULT_GEN_PREC_N ; 
 size_t SECP256K1_ECMULT_GEN_CONTEXT_PREALLOCATED_SIZE ; 
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 scalar_t__ manual_alloc (void**,size_t const,void* const,size_t const) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_blind (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_ecmult_static_context ; 
 int secp256k1_fe_set_b32 (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_ge_set_all_gej_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int secp256k1_ge_set_xo_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_ge_to_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_add_ge_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_add_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_double_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void secp256k1_ecmult_gen_context_build(secp256k1_ecmult_gen_context *ctx, void **prealloc) {
#ifndef USE_ECMULT_STATIC_PRECOMPUTATION
    secp256k1_ge prec[ECMULT_GEN_PREC_N * ECMULT_GEN_PREC_G];
    secp256k1_gej gj;
    secp256k1_gej nums_gej;
    int i, j;
    size_t const prealloc_size = SECP256K1_ECMULT_GEN_CONTEXT_PREALLOCATED_SIZE;
    void* const base = *prealloc;
#endif

    if (ctx->prec != NULL) {
        return;
    }
#ifndef USE_ECMULT_STATIC_PRECOMPUTATION
    ctx->prec = (secp256k1_ge_storage (*)[ECMULT_GEN_PREC_N][ECMULT_GEN_PREC_G])manual_alloc(prealloc, prealloc_size, base, prealloc_size);

    /* get the generator */
    secp256k1_gej_set_ge(&gj, &secp256k1_ge_const_g);

    /* Construct a group element with no known corresponding scalar (nothing up my sleeve). */
    {
        static const unsigned char nums_b32[33] = "The scalar for this x is unknown";
        secp256k1_fe nums_x;
        secp256k1_ge nums_ge;
        int r;
        r = secp256k1_fe_set_b32(&nums_x, nums_b32);
        (void)r;
        VERIFY_CHECK(r);
        r = secp256k1_ge_set_xo_var(&nums_ge, &nums_x, 0);
        (void)r;
        VERIFY_CHECK(r);
        secp256k1_gej_set_ge(&nums_gej, &nums_ge);
        /* Add G to make the bits in x uniformly distributed. */
        secp256k1_gej_add_ge_var(&nums_gej, &nums_gej, &secp256k1_ge_const_g, NULL);
    }

    /* compute prec. */
    {
        secp256k1_gej precj[ECMULT_GEN_PREC_N * ECMULT_GEN_PREC_G]; /* Jacobian versions of prec. */
        secp256k1_gej gbase;
        secp256k1_gej numsbase;
        gbase = gj; /* PREC_G^j * G */
        numsbase = nums_gej; /* 2^j * nums. */
        for (j = 0; j < ECMULT_GEN_PREC_N; j++) {
            /* Set precj[j*PREC_G .. j*PREC_G+(PREC_G-1)] to (numsbase, numsbase + gbase, ..., numsbase + (PREC_G-1)*gbase). */
            precj[j*ECMULT_GEN_PREC_G] = numsbase;
            for (i = 1; i < ECMULT_GEN_PREC_G; i++) {
                secp256k1_gej_add_var(&precj[j*ECMULT_GEN_PREC_G + i], &precj[j*ECMULT_GEN_PREC_G + i - 1], &gbase, NULL);
            }
            /* Multiply gbase by PREC_G. */
            for (i = 0; i < ECMULT_GEN_PREC_B; i++) {
                secp256k1_gej_double_var(&gbase, &gbase, NULL);
            }
            /* Multiply numbase by 2. */
            secp256k1_gej_double_var(&numsbase, &numsbase, NULL);
            if (j == ECMULT_GEN_PREC_N - 2) {
                /* In the last iteration, numsbase is (1 - 2^j) * nums instead. */
                secp256k1_gej_neg(&numsbase, &numsbase);
                secp256k1_gej_add_var(&numsbase, &numsbase, &nums_gej, NULL);
            }
        }
        secp256k1_ge_set_all_gej_var(prec, precj, ECMULT_GEN_PREC_N * ECMULT_GEN_PREC_G);
    }
    for (j = 0; j < ECMULT_GEN_PREC_N; j++) {
        for (i = 0; i < ECMULT_GEN_PREC_G; i++) {
            secp256k1_ge_to_storage(&(*ctx->prec)[j][i], &prec[j*ECMULT_GEN_PREC_G + i]);
        }
    }
#else
    (void)prealloc;
    ctx->prec = (secp256k1_ge_storage (*)[ECMULT_GEN_PREC_N][ECMULT_GEN_PREC_G])secp256k1_ecmult_static_context;
#endif
    secp256k1_ecmult_gen_blind(ctx, NULL);
}