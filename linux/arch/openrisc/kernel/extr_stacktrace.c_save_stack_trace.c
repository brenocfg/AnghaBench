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
 int /*<<< orphan*/  save_stack_address ; 
 int /*<<< orphan*/  unwind_stack (struct stack_trace*,unsigned long*,int /*<<< orphan*/ ) ; 

void save_stack_trace(struct stack_trace *trace)
{
	unwind_stack(trace, (unsigned long *) &trace, save_stack_address);
}