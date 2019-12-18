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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ bench_recover_data ;

/* Variables and functions */
 int /*<<< orphan*/  SECP256K1_CONTEXT_VERIFY ; 
 int /*<<< orphan*/  bench_recover ; 
 int /*<<< orphan*/  bench_recover_setup ; 
 int /*<<< orphan*/  run_benchmark (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  secp256k1_context_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (int /*<<< orphan*/ ) ; 

int main(void) {
    bench_recover_data data;

    data.ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);

    run_benchmark("ecdsa_recover", bench_recover, bench_recover_setup, NULL, &data, 10, 20000);

    secp256k1_context_destroy(data.ctx);
    return 0;
}