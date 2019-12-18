#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {unsigned int focus_core; scalar_t__ focus_switch; scalar_t__ step_isr; } ;
typedef  TYPE_1__ cvmx_debug_state_t ;

/* Variables and functions */
 int ISR_DELAY_COUNTER ; 
 TYPE_1__ cvmx_debug_get_state () ; 
 int /*<<< orphan*/  cvmx_debug_printf (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void cvmx_debug_delay_isr_core(unsigned core, uint32_t depc, int single_stepped_exc_only,
                                      cvmx_debug_state_t state)
{
    volatile uint64_t i;
    if(!single_stepped_exc_only || state.step_isr || core == state.focus_core || state.focus_switch)
        return;

    cvmx_debug_printf ("Core #%u spinning for focus at 0x%x\n", core, (unsigned int)depc);

    for(i = ISR_DELAY_COUNTER; i > 0 ; i--)
    {
       state = cvmx_debug_get_state();
       /* Spin giving the focus core time to service ISR */
       /* But cut short the loop, if we can.  Shrink down i, only once. */
       if (i > 600000 && state.focus_switch)
           i = 500000;
    }
    
}