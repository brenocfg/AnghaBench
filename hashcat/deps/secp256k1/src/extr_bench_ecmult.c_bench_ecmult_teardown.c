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
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_2__ {int count; int /*<<< orphan*/ * expected_output; int /*<<< orphan*/ * output; } ;
typedef  TYPE_1__ bench_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int ITERS ; 
 int /*<<< orphan*/  secp256k1_gej_add_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_is_infinity (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bench_ecmult_teardown(void* arg) {
    bench_data* data = (bench_data*)arg;
    size_t iters = 1 + ITERS / data->count;
    size_t iter;
    /* Verify the results in teardown, to avoid doing comparisons while benchmarking. */
    for (iter = 0; iter < iters; ++iter) {
        secp256k1_gej tmp;
        secp256k1_gej_add_var(&tmp, &data->output[iter], &data->expected_output[iter], NULL);
        CHECK(secp256k1_gej_is_infinity(&tmp));
    }
}