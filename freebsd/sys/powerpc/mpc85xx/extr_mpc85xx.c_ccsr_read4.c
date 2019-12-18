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
typedef  int /*<<< orphan*/  volatile uint32_t ;

/* Variables and functions */

uint32_t
ccsr_read4(uintptr_t addr)
{
	volatile uint32_t *ptr = (void *)addr;

	return (*ptr);
}