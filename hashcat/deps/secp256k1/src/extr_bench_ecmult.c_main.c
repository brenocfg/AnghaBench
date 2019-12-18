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
struct TYPE_3__ {int /*<<< orphan*/ * expected_output; int /*<<< orphan*/ * output; int /*<<< orphan*/ * seckeys; int /*<<< orphan*/ * pubkeys; int /*<<< orphan*/ * scalars; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * scratch; void* ecmult_multi; } ;
typedef  TYPE_1__ bench_data ;

/* Variables and functions */
 int ITERS ; 
 int POINTS ; 
 int SECP256K1_CONTEXT_SIGN ; 
 int SECP256K1_CONTEXT_VERIFY ; 
 int STRAUSS_SCRATCH_OBJECTS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_scalar (int,int /*<<< orphan*/ *) ; 
 scalar_t__ have_flag (int,char**,char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_test (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  secp256k1_context_create (int) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (int /*<<< orphan*/ ) ; 
 void* secp256k1_ecmult_multi_var ; 
 void* secp256k1_ecmult_pippenger_batch_single ; 
 void* secp256k1_ecmult_strauss_batch_single ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_ge_set_all_gej_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_gej_double_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * secp256k1_scratch_space_create (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  secp256k1_scratch_space_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int secp256k1_strauss_scratch_size (int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv) {
    bench_data data;
    int i, p;
    secp256k1_gej* pubkeys_gej;
    size_t scratch_size;

    data.ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    scratch_size = secp256k1_strauss_scratch_size(POINTS) + STRAUSS_SCRATCH_OBJECTS*16;
    data.scratch = secp256k1_scratch_space_create(data.ctx, scratch_size);
    data.ecmult_multi = secp256k1_ecmult_multi_var;

    if (argc > 1) {
        if(have_flag(argc, argv, "pippenger_wnaf")) {
            printf("Using pippenger_wnaf:\n");
            data.ecmult_multi = secp256k1_ecmult_pippenger_batch_single;
        } else if(have_flag(argc, argv, "strauss_wnaf")) {
            printf("Using strauss_wnaf:\n");
            data.ecmult_multi = secp256k1_ecmult_strauss_batch_single;
        } else if(have_flag(argc, argv, "simple")) {
            printf("Using simple algorithm:\n");
            data.ecmult_multi = secp256k1_ecmult_multi_var;
            secp256k1_scratch_space_destroy(data.ctx, data.scratch);
            data.scratch = NULL;
        } else {
            fprintf(stderr, "%s: unrecognized argument '%s'.\n", argv[0], argv[1]);
            fprintf(stderr, "Use 'pippenger_wnaf', 'strauss_wnaf', 'simple' or no argument to benchmark a combined algorithm.\n");
            return 1;
        }
    }

    /* Allocate stuff */
    data.scalars = malloc(sizeof(secp256k1_scalar) * POINTS);
    data.seckeys = malloc(sizeof(secp256k1_scalar) * POINTS);
    data.pubkeys = malloc(sizeof(secp256k1_ge) * POINTS);
    data.expected_output = malloc(sizeof(secp256k1_gej) * (ITERS + 1));
    data.output = malloc(sizeof(secp256k1_gej) * (ITERS + 1));

    /* Generate a set of scalars, and private/public keypairs. */
    pubkeys_gej = malloc(sizeof(secp256k1_gej) * POINTS);
    secp256k1_gej_set_ge(&pubkeys_gej[0], &secp256k1_ge_const_g);
    secp256k1_scalar_set_int(&data.seckeys[0], 1);
    for (i = 0; i < POINTS; ++i) {
        generate_scalar(i, &data.scalars[i]);
        if (i) {
            secp256k1_gej_double_var(&pubkeys_gej[i], &pubkeys_gej[i - 1], NULL);
            secp256k1_scalar_add(&data.seckeys[i], &data.seckeys[i - 1], &data.seckeys[i - 1]);
        }
    }
    secp256k1_ge_set_all_gej_var(data.pubkeys, pubkeys_gej, POINTS);
    free(pubkeys_gej);

    for (i = 1; i <= 8; ++i) {
        run_test(&data, i, 1);
    }

    for (p = 0; p <= 11; ++p) {
        for (i = 9; i <= 16; ++i) {
            run_test(&data, i << p, 1);
        }
    }
    if (data.scratch != NULL) {
        secp256k1_scratch_space_destroy(data.ctx, data.scratch);
    }
    secp256k1_context_destroy(data.ctx);
    free(data.scalars);
    free(data.pubkeys);
    free(data.seckeys);
    free(data.output);
    free(data.expected_output);

    return(0);
}