#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* perfctrl; } ;
struct TYPE_8__ {TYPE_1__ cop0; } ;
typedef  TYPE_3__ cvmx_debug_core_context_t ;
struct TYPE_7__ {int u; int s; int k; int ex; int w; int m; int event; } ;
struct TYPE_9__ {scalar_t__ u32; TYPE_2__ s; } ;
typedef  TYPE_4__ cvmx_core_perf_control_t ;

/* Variables and functions */

__attribute__((used)) static void cvmx_debug_set_perf_control_reg (volatile cvmx_debug_core_context_t *context, int perf_event, int perf_counter)
{
    cvmx_core_perf_control_t control;

    control.u32 = 0;
    control.s.u = 1;
    control.s.s = 1;
    control.s.k = 1;
    control.s.ex = 1;
    control.s.w = 1;
    control.s.m = 1 - perf_counter;
    control.s.event = perf_event;

    context->cop0.perfctrl[perf_counter] = control.u32;
}