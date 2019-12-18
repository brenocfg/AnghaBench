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
struct TYPE_2__ {int end; } ;
struct unwind_state {unsigned long sp; TYPE_1__ stack_info; } ;
struct stack_frame {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool outside_of_stack(struct unwind_state *state, unsigned long sp)
{
	return (sp <= state->sp) ||
		(sp > state->stack_info.end - sizeof(struct stack_frame));
}