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
typedef  int u_char ;
typedef  scalar_t__ cy_addr ;

/* Variables and functions */
 int /*<<< orphan*/  CD1400_CCR ; 
 int CD1400_CCR_CMDRESET ; 
 int CD1400_CCR_FULLRESET ; 
 int /*<<< orphan*/  CD1400_GFRCR ; 
 int CY_MAX_CD1400s ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int cd_inb (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cd_outb (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int* cy_chip_offset ; 

int
cy_units(cy_addr cy_iobase, int cy_align)
{
	int	cyu;
	u_char	firmware_version;
	int	i;
	cy_addr	iobase;

	for (cyu = 0; cyu < CY_MAX_CD1400s; ++cyu) {
		iobase = cy_iobase + (cy_chip_offset[cyu] << cy_align);

		/* wait for chip to become ready for new command */
		for (i = 0; i < 10; i++) {
			DELAY(50);
			if (!cd_inb(iobase, CD1400_CCR, cy_align))
				break;
		}

		/* clear the GFRCR register */
		cd_outb(iobase, CD1400_GFRCR, cy_align, 0);

		/* issue a reset command */
		cd_outb(iobase, CD1400_CCR, cy_align,
			CD1400_CCR_CMDRESET | CD1400_CCR_FULLRESET);

		/* XXX bogus initialization to avoid a gcc bug/warning. */
		firmware_version = 0;

		/* wait for the CD1400 to initialize itself */
		for (i = 0; i < 200; i++) {
			DELAY(50);

			/* retrieve firmware version */
			firmware_version = cd_inb(iobase, CD1400_GFRCR,
						  cy_align);
			if ((firmware_version & 0xf0) == 0x40)
				break;
		}

		/*
		 * Anything in the 0x40-0x4F range is fine.
		 * If one CD1400 is bad then we don't support higher
		 * numbered good ones on this board.
		 */
		if ((firmware_version & 0xf0) != 0x40)
			break;
	}
	return (cyu);
}