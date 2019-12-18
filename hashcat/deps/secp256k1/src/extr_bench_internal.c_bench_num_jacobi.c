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
typedef  int /*<<< orphan*/  secp256k1_num ;
struct TYPE_2__ {int /*<<< orphan*/  scalar_y; int /*<<< orphan*/  scalar_x; } ;
typedef  TYPE_1__ bench_inv ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_num_jacobi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_order_get_num (int /*<<< orphan*/ *) ; 

void bench_num_jacobi(void* arg) {
    int i;
    bench_inv *data = (bench_inv*)arg;
    secp256k1_num nx, norder;

    secp256k1_scalar_get_num(&nx, &data->scalar_x);
    secp256k1_scalar_order_get_num(&norder);
    secp256k1_scalar_get_num(&norder, &data->scalar_y);

    for (i = 0; i < 200000; i++) {
        secp256k1_num_jacobi(&nx, &norder);
    }
}