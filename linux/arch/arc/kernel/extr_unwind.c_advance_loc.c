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
struct unwind_state {unsigned long loc; unsigned long codeAlign; } ;

/* Variables and functions */
 int /*<<< orphan*/  unw_debug (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int advance_loc(unsigned long delta, struct unwind_state *state)
{
	state->loc += delta * state->codeAlign;

	/* FIXME_Rajesh: Probably we are defining for the initial range as well;
	   return delta > 0;
	 */
	unw_debug("delta %3lu => loc 0x%lx: ", delta, state->loc);
	return 1;
}