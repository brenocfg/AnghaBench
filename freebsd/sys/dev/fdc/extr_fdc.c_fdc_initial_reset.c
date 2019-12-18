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
struct fdc_data {int /*<<< orphan*/  fdct; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  FDC_ENHANCED ; 
 int /*<<< orphan*/  FDC_NE765 ; 
 int /*<<< orphan*/  FDC_UNKNOWN ; 
 int /*<<< orphan*/  FDO_FRST ; 
 int /*<<< orphan*/  NE7CMD_SPECIFY ; 
 int NE7CMD_VERSION ; 
 int /*<<< orphan*/  NE7_SPEC_1 (int,int) ; 
 int /*<<< orphan*/  NE7_SPEC_2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fdc_cmd (struct fdc_data*,int,int,int,int*,...) ; 
 int /*<<< orphan*/  fdout_wr (struct fdc_data*,int /*<<< orphan*/ ) ; 
 int fdsts_rd (struct fdc_data*) ; 

int
fdc_initial_reset(device_t dev, struct fdc_data *fdc)
{
	int ic_type, part_id;

	/*
	 * A status value of 0xff is very unlikely, but not theoretically
	 * impossible, but it is far more likely to indicate an empty bus.
	 */
	if (fdsts_rd(fdc) == 0xff)
		return (ENXIO);

	/*
	 * Assert a reset to the floppy controller and check that the status
	 * register goes to zero.
	 */
	fdout_wr(fdc, 0);
	fdout_wr(fdc, 0);
	if (fdsts_rd(fdc) != 0)
		return (ENXIO);

	/*
	 * Clear the reset and see it come ready.
	 */
	fdout_wr(fdc, FDO_FRST);
	DELAY(100);
	if (fdsts_rd(fdc) != 0x80)
		return (ENXIO);

	/* Then, see if it can handle a command. */
	if (fdc_cmd(fdc, 3, NE7CMD_SPECIFY, NE7_SPEC_1(6, 240),
	    NE7_SPEC_2(31, 0), 0))
		return (ENXIO);

	/*
	 * Try to identify the chip.
	 *
	 * The i8272 datasheet documents that unknown commands
	 * will return ST0 as 0x80.  The i8272 is supposedly identical
	 * to the NEC765.
	 * The i82077SL datasheet says 0x90 for the VERSION command,
	 * and several "superio" chips emulate this.
	 */
	if (fdc_cmd(fdc, 1, NE7CMD_VERSION, 1, &ic_type))
		return (ENXIO);
	if (fdc_cmd(fdc, 1, 0x18, 1, &part_id))
		return (ENXIO);
	if (bootverbose)
		device_printf(dev,
		    "ic_type %02x part_id %02x\n", ic_type, part_id);
	switch (ic_type & 0xff) {
	case 0x80:
		device_set_desc(dev, "NEC 765 or clone");
		fdc->fdct = FDC_NE765;
		break;
	case 0x81:
	case 0x90:
		device_set_desc(dev,
		    "Enhanced floppy controller");
		fdc->fdct = FDC_ENHANCED;
		break;
	default:
		device_set_desc(dev, "Generic floppy controller");
		fdc->fdct = FDC_UNKNOWN;
		break;
	}
	return (0);
}