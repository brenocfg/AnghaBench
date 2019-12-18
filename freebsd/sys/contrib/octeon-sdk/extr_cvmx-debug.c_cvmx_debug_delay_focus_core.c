#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int focus_core; } ;
typedef  TYPE_2__ cvmx_debug_state_t ;
struct TYPE_6__ {scalar_t__ dbp; scalar_t__ dss; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_debug_register_t ;

/* Variables and functions */

__attribute__((used)) static void cvmx_debug_delay_focus_core(cvmx_debug_state_t state, unsigned core, cvmx_debug_register_t *debug_reg)
{
    volatile int i;
    if (debug_reg->s.dss || debug_reg->s.dbp || core != state.focus_core)
        return;
    for (i = 0; i < 2400; i++)
    {
        asm volatile (".set push		\n\t"
                      ".set noreorder		\n\t"
                      "nop			\n\t"
                      "nop			\n\t"
                      "nop			\n\t"
                      "nop			\n\t"
                      ".set pop");
        /* Spin giving the breakpoint core time to steal focus */
    }

}