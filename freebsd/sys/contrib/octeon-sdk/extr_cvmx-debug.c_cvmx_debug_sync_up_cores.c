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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__* state; } ;

/* Variables and functions */
 TYPE_1__* cvmx_debug_globals ; 
 int /*<<< orphan*/  cvmx_debug_state_t ; 
 int /*<<< orphan*/  handler_cores ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_all ; 

__attribute__((used)) static void cvmx_debug_sync_up_cores(void)
{
    /* NOTE this reads directly from the state array for speed reasons
       and we don't change the array. */
    do {
      asm("": : : "memory");
    } while (cvmx_debug_globals->state[offsetof(cvmx_debug_state_t, step_all)/sizeof(uint32_t)]
	     && cvmx_debug_globals->state[offsetof(cvmx_debug_state_t, handler_cores)/sizeof(uint32_t)] != 0);
}