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
typedef  scalar_t__ u_register_t ;

/* Variables and functions */

__attribute__((used)) static u_register_t
stack_register_fetch(u_register_t sp, u_register_t stack_pos)
{
	u_register_t * stack = 
	    ((u_register_t *)(intptr_t)sp + (size_t)stack_pos/sizeof(u_register_t));

	return *stack;
}