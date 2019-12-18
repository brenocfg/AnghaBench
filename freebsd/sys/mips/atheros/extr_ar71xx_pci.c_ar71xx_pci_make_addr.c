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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
ar71xx_pci_make_addr(int bus, int slot, int func, int reg)
{
	if (bus == 0) {
		return ((1 << slot) | (func << 8) | (reg & ~3));
	} else {
		return ((bus << 16) | (slot << 11) | (func << 8)
		    | (reg  & ~3) | 1);
	}
}