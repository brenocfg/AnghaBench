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
struct stack_trace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_do_save_stack ; 
 int /*<<< orphan*/  unw_init_running (int /*<<< orphan*/ ,struct stack_trace*) ; 

void save_stack_trace(struct stack_trace *trace)
{
	unw_init_running(ia64_do_save_stack, trace);
}