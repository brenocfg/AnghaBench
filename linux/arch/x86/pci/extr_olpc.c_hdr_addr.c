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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ bar_probing ; 

__attribute__((used)) static uint32_t *hdr_addr(const uint32_t *hdr, int reg)
{
	uint32_t addr;

	/*
	 * This is a little bit tricky.  The header maps consist of
	 * 0x20 bytes of size masks, followed by 0x70 bytes of header data.
	 * In the normal case, when not probing a BAR's size, we want
	 * to access the header data, so we add 0x20 to the reg offset,
	 * thus skipping the size mask area.
	 * In the BAR probing case, we want to access the size mask for
	 * the BAR, so we subtract 0x10 (the config header offset for
	 * BAR0), and don't skip the size mask area.
	 */

	addr = (uint32_t)hdr + reg + (bar_probing ? -0x10 : 0x20);

	bar_probing = 0;
	return (uint32_t *)addr;
}