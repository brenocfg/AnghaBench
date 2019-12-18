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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct axp_mc_drvdata {int width; scalar_t__* cs_addr_sel; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t axp_mc_calc_address(struct axp_mc_drvdata *drvdata,
				    uint8_t cs, uint8_t bank, uint16_t row,
				    uint16_t col)
{
	if (drvdata->width == 8) {
		/* 64 bit */
		if (drvdata->cs_addr_sel[cs])
			/* bank interleaved */
			return (((row & 0xfff8) << 16) |
				((bank & 0x7) << 16) |
				((row & 0x7) << 13) |
				((col & 0x3ff) << 3));
		else
			return (((row & 0xffff << 16) |
				 ((bank & 0x7) << 13) |
				 ((col & 0x3ff)) << 3));
	} else if (drvdata->width == 4) {
		/* 32 bit */
		if (drvdata->cs_addr_sel[cs])
			/* bank interleaved */
			return (((row & 0xfff0) << 15) |
				((bank & 0x7) << 16) |
				((row & 0xf) << 12) |
				((col & 0x3ff) << 2));
		else
			return (((row & 0xffff << 15) |
				 ((bank & 0x7) << 12) |
				 ((col & 0x3ff)) << 2));
	} else {
		/* 16 bit */
		if (drvdata->cs_addr_sel[cs])
			/* bank interleaved */
			return (((row & 0xffe0) << 14) |
				((bank & 0x7) << 16) |
				((row & 0x1f) << 11) |
				((col & 0x3ff) << 1));
		else
			return (((row & 0xffff << 14) |
				 ((bank & 0x7) << 11) |
				 ((col & 0x3ff)) << 1));
	}
}