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
 scalar_t__ HPET_MMIO_ADDR ; 

__attribute__((used)) static int hpet_read(int offset)
{
	return *(volatile unsigned int *)(HPET_MMIO_ADDR + offset);
}