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
typedef  unsigned int u_int ;
struct iomux_softc {int dummy; } ;

/* Variables and functions */
 unsigned int RD4 (struct iomux_softc*,scalar_t__) ; 
 int /*<<< orphan*/  WR4 (struct iomux_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
iomux_configure_input(struct iomux_softc *sc, uint32_t reg, uint32_t val)
{
	u_int select, mask, shift, width;

	/* If register and value are zero, there is nothing to configure. */
	if (reg == 0 && val == 0)
		return;

	/*
	 * If the config value has 0xff in the high byte it is encoded:
	 * 	31     23      15      7        0
	 *      | 0xff | shift | width | select |
	 * We need to mask out the old select value and OR in the new, using a
	 * mask of the given width and shifting the values up by shift.
	 */
	if ((val & 0xff000000) == 0xff000000) {
		select = val & 0x000000ff;
		width = (val & 0x0000ff00) >> 8;
		shift = (val & 0x00ff0000) >> 16;
		mask  = ((1u << width) - 1) << shift;
		val = (RD4(sc, reg) & ~mask) | (select << shift);
	}
	WR4(sc, reg, val);
}