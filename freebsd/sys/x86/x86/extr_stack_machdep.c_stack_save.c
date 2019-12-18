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
struct stack {int dummy; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  stack_capture (int /*<<< orphan*/ ,struct stack*,int /*<<< orphan*/ ) ; 

void
stack_save(struct stack *st)
{
	register_t fp;

#ifdef __i386__
	__asm __volatile("movl %%ebp,%0" : "=g" (fp));
#else
	__asm __volatile("movq %%rbp,%0" : "=g" (fp));
#endif
	stack_capture(curthread, st, fp);
}