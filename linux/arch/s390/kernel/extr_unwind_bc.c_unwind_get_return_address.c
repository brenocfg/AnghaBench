#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct unwind_state {unsigned long ip; } ;

/* Variables and functions */
 scalar_t__ __kernel_text_address (unsigned long) ; 
 scalar_t__ unwind_done (struct unwind_state*) ; 

unsigned long unwind_get_return_address(struct unwind_state *state)
{
	if (unwind_done(state))
		return 0;
	return __kernel_text_address(state->ip) ? state->ip : 0;
}