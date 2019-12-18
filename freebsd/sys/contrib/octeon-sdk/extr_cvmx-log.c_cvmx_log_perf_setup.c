#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* cvmx_core_perf_t ;
struct TYPE_3__ {int u; int s; int k; int ex; void* event; } ;
struct TYPE_4__ {TYPE_1__ s; scalar_t__ u32; } ;
typedef  TYPE_2__ cvmx_core_perf_control_t ;

/* Variables and functions */

void cvmx_log_perf_setup(cvmx_core_perf_t counter1, cvmx_core_perf_t counter2)
{
    cvmx_core_perf_control_t control;

    control.u32 = 0;
    control.s.event = counter1;
    control.s.u = 1;
    control.s.s = 1;
    control.s.k = 1;
    control.s.ex = 1;
    asm ("mtc0 %0, $25, 0\n" : : "r"(control.u32));
    control.s.event = counter2;
    asm ("mtc0 %0, $25, 2\n" : : "r"(control.u32));
}