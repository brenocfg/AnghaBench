#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 size_t ECMULT_MAX_POINTS_PER_BATCH ; 
 size_t SIZE_MAX ; 
 int secp256k1_ecmult_multi_batch_size_helper (size_t*,size_t*,size_t,size_t) ; 

void test_ecmult_multi_batch_size_helper(void) {
    size_t n_batches, n_batch_points, max_n_batch_points, n;

    max_n_batch_points = 0;
    n = 1;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 0);

    max_n_batch_points = 1;
    n = 0;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 1);
    CHECK(n_batches == 0);
    CHECK(n_batch_points == 0);

    max_n_batch_points = 2;
    n = 5;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 1);
    CHECK(n_batches == 3);
    CHECK(n_batch_points == 2);

    max_n_batch_points = ECMULT_MAX_POINTS_PER_BATCH;
    n = ECMULT_MAX_POINTS_PER_BATCH;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 1);
    CHECK(n_batches == 1);
    CHECK(n_batch_points == ECMULT_MAX_POINTS_PER_BATCH);

    max_n_batch_points = ECMULT_MAX_POINTS_PER_BATCH + 1;
    n = ECMULT_MAX_POINTS_PER_BATCH + 1;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 1);
    CHECK(n_batches == 2);
    CHECK(n_batch_points == ECMULT_MAX_POINTS_PER_BATCH/2 + 1);

    max_n_batch_points = 1;
    n = SIZE_MAX;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 1);
    CHECK(n_batches == SIZE_MAX);
    CHECK(n_batch_points == 1);

    max_n_batch_points = 2;
    n = SIZE_MAX;
    CHECK(secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, max_n_batch_points, n) == 1);
    CHECK(n_batches == SIZE_MAX/2 + 1);
    CHECK(n_batch_points == 2);
}