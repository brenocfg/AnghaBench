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
 int /*<<< orphan*/  CHECK (int) ; 
 int PIPPENGER_MAX_BUCKET_WINDOW ; 
 int PIPPENGER_SCRATCH_OBJECTS ; 
 TYPE_1__* ctx ; 
 int secp256k1_pippenger_bucket_window (size_t) ; 
 size_t secp256k1_pippenger_bucket_window_inv (int) ; 
 size_t secp256k1_pippenger_max_points (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t secp256k1_pippenger_scratch_size (size_t,int) ; 
 size_t secp256k1_rand_int (int) ; 
 int secp256k1_scratch_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  secp256k1_scratch_apply_checkpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t secp256k1_scratch_checkpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * secp256k1_scratch_create (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  secp256k1_scratch_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_ecmult_multi_pippenger_max_points(void) {
    size_t scratch_size = secp256k1_rand_int(256);
    size_t max_size = secp256k1_pippenger_scratch_size(secp256k1_pippenger_bucket_window_inv(PIPPENGER_MAX_BUCKET_WINDOW-1)+512, 12);
    secp256k1_scratch *scratch;
    size_t n_points_supported;
    int bucket_window = 0;

    for(; scratch_size < max_size; scratch_size+=256) {
        size_t i;
        size_t total_alloc;
        size_t checkpoint;
        scratch = secp256k1_scratch_create(&ctx->error_callback, scratch_size);
        CHECK(scratch != NULL);
        checkpoint = secp256k1_scratch_checkpoint(&ctx->error_callback, scratch);
        n_points_supported = secp256k1_pippenger_max_points(&ctx->error_callback, scratch);
        if (n_points_supported == 0) {
            secp256k1_scratch_destroy(&ctx->error_callback, scratch);
            continue;
        }
        bucket_window = secp256k1_pippenger_bucket_window(n_points_supported);
        /* allocate `total_alloc` bytes over `PIPPENGER_SCRATCH_OBJECTS` many allocations */
        total_alloc = secp256k1_pippenger_scratch_size(n_points_supported, bucket_window);
        for (i = 0; i < PIPPENGER_SCRATCH_OBJECTS - 1; i++) {
            CHECK(secp256k1_scratch_alloc(&ctx->error_callback, scratch, 1));
            total_alloc--;
        }
        CHECK(secp256k1_scratch_alloc(&ctx->error_callback, scratch, total_alloc));
        secp256k1_scratch_apply_checkpoint(&ctx->error_callback, scratch, checkpoint);
        secp256k1_scratch_destroy(&ctx->error_callback, scratch);
    }
    CHECK(bucket_window == PIPPENGER_MAX_BUCKET_WINDOW);
}