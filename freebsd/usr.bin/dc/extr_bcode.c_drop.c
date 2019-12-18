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
struct value {int dummy; } ;

/* Variables and functions */
 struct value* pop () ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 

__attribute__((used)) static void
drop(void)
{
	struct value *v = pop();
	if (v != NULL)
		stack_free_value(v);
}