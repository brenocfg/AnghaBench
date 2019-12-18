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

/* Variables and functions */

void *set_exception_table_vec(unsigned int vec, void *handler)
{
	extern void *exception_handling_table[];
	void *old_handler;

	old_handler = exception_handling_table[vec];
	exception_handling_table[vec] = handler;
	return old_handler;
}