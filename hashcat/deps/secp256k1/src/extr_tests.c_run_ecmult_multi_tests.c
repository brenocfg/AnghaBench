#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scratch ;
struct TYPE_2__ {int /*<<< orphan*/  error_callback; } ;

/* Variables and functions */
 int ALIGNMENT ; 
 int STRAUSS_SCRATCH_OBJECTS ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  secp256k1_ecmult_multi_var ; 
 int /*<<< orphan*/  secp256k1_ecmult_pippenger_batch_single ; 
 int /*<<< orphan*/  secp256k1_ecmult_strauss_batch_single ; 
 int /*<<< orphan*/ * secp256k1_scratch_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_scratch_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_strauss_scratch_size (int) ; 
 int /*<<< orphan*/  test_ecmult_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ecmult_multi_batch_single (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ecmult_multi_batch_size_helper () ; 
 int /*<<< orphan*/  test_ecmult_multi_batching () ; 
 int /*<<< orphan*/  test_ecmult_multi_pippenger_max_points () ; 
 int /*<<< orphan*/  test_secp256k1_pippenger_bucket_window_inv () ; 

void run_ecmult_multi_tests(void) {
    secp256k1_scratch *scratch;

    test_secp256k1_pippenger_bucket_window_inv();
    test_ecmult_multi_pippenger_max_points();
    scratch = secp256k1_scratch_create(&ctx->error_callback, 819200);
    test_ecmult_multi(scratch, secp256k1_ecmult_multi_var);
    test_ecmult_multi(NULL, secp256k1_ecmult_multi_var);
    test_ecmult_multi(scratch, secp256k1_ecmult_pippenger_batch_single);
    test_ecmult_multi_batch_single(secp256k1_ecmult_pippenger_batch_single);
    test_ecmult_multi(scratch, secp256k1_ecmult_strauss_batch_single);
    test_ecmult_multi_batch_single(secp256k1_ecmult_strauss_batch_single);
    secp256k1_scratch_destroy(&ctx->error_callback, scratch);

    /* Run test_ecmult_multi with space for exactly one point */
    scratch = secp256k1_scratch_create(&ctx->error_callback, secp256k1_strauss_scratch_size(1) + STRAUSS_SCRATCH_OBJECTS*ALIGNMENT);
    test_ecmult_multi(scratch, secp256k1_ecmult_multi_var);
    secp256k1_scratch_destroy(&ctx->error_callback, scratch);

    test_ecmult_multi_batch_size_helper();
    test_ecmult_multi_batching();
}