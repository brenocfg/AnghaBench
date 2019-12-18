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
struct TYPE_2__ {int offset1; int count; int offset2; } ;
typedef  TYPE_1__ bench_data ;

/* Variables and functions */
 int POINTS ; 

__attribute__((used)) static void bench_ecmult_setup(void* arg) {
    bench_data* data = (bench_data*)arg;
    data->offset1 = (data->count * 0x537b7f6f + 0x8f66a481) % POINTS;
    data->offset2 = (data->count * 0x7f6f537b + 0x6a1a8f49) % POINTS;
}