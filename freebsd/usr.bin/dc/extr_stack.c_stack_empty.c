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
struct stack {int sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static __inline bool
stack_empty(const struct stack *stack)
{
	bool empty = stack->sp == -1;

	if (empty)
		warnx("stack empty");
	return empty;
}