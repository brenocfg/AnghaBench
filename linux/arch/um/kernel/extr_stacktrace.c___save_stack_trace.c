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
struct task_struct {int dummy; } ;
struct stack_trace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_ops ; 
 int /*<<< orphan*/  dump_trace (struct task_struct*,int /*<<< orphan*/ *,struct stack_trace*) ; 

__attribute__((used)) static void __save_stack_trace(struct task_struct *tsk, struct stack_trace *trace)
{
	dump_trace(tsk, &dump_ops, trace);
}