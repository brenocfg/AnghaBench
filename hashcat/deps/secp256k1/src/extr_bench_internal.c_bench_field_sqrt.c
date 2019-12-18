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
typedef  int /*<<< orphan*/  secp256k1_fe ;
struct TYPE_2__ {int /*<<< orphan*/  fe_y; int /*<<< orphan*/  fe_x; } ;
typedef  TYPE_1__ bench_inv ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_fe_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_sqrt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bench_field_sqrt(void* arg) {
    int i;
    bench_inv *data = (bench_inv*)arg;
    secp256k1_fe t;

    for (i = 0; i < 20000; i++) {
        t = data->fe_x;
        secp256k1_fe_sqrt(&data->fe_x, &t);
        secp256k1_fe_add(&data->fe_x, &data->fe_y);
    }
}