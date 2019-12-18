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
struct TYPE_2__ {int /*<<< orphan*/  gej_x; } ;
typedef  TYPE_1__ bench_inv ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_gej_has_quad_y_var (int /*<<< orphan*/ *) ; 

void bench_group_jacobi_var(void* arg) {
    int i;
    bench_inv *data = (bench_inv*)arg;

    for (i = 0; i < 20000; i++) {
        secp256k1_gej_has_quad_y_var(&data->gej_x);
    }
}