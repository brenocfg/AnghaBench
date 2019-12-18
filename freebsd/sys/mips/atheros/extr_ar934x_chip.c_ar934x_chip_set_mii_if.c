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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static void
ar934x_chip_set_mii_if(uint32_t unit, uint32_t mii_mode)
{

	/*
	 * XXX !
	 *
	 * Nothing to see here; although gmac0 can have its
	 * MII configuration changed, the register values
	 * are slightly different.
	 */
}