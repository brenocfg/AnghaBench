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
 unsigned long __hbird_read_stick () ; 
 int /*<<< orphan*/  __hbird_write_stick (unsigned long) ; 

__attribute__((used)) static unsigned long hbtick_add_tick(unsigned long adj)
{
	unsigned long val;

	val = __hbird_read_stick() + adj;
	__hbird_write_stick(val);

	return val;
}