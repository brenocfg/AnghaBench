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
 int /*<<< orphan*/  c6x_halt () ; 
 int /*<<< orphan*/  halt_loop () ; 

void machine_halt(void)
{
	if (c6x_halt)
		c6x_halt();
	halt_loop();
}