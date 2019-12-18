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
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ OMAP4430_REV_ES1_0 ; 
 scalar_t__ OMAP4430_REV_ES2_1 ; 
 scalar_t__ OMAP4430_REV_ES2_2 ; 
 scalar_t__ OMAP4430_REV_ES2_3 ; 
 scalar_t__ OMAP4430_REV_UNKNOWN ; 
 scalar_t__ OMAP4460_REV_ES1_0 ; 
 scalar_t__ OMAP4460_REV_ES1_1 ; 
 scalar_t__ OMAP4460_REV_UNKNOWN ; 
 scalar_t__ OMAP4470_REV_ES1_0 ; 
 scalar_t__ OMAP4470_REV_UNKNOWN ; 
 int /*<<< orphan*/  OMAP44XX_L4_CORE_HWBASE ; 
 int /*<<< orphan*/  OMAP4_ID_CODE ; 
 int OMAP_REV_DEVICE (scalar_t__) ; 
 int OMAP_REV_MAJOR (scalar_t__) ; 
 int OMAP_REV_MINOR (scalar_t__) ; 
 scalar_t__ OMAP_UNKNOWN_DEV ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chip_revision ; 
 int cp15_midr_get () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static void
omap4_get_revision(void)
{
	uint32_t id_code;
	uint32_t revision;
	uint32_t hawkeye;
	bus_space_handle_t bsh;

	/* The chip revsion is read from the device identification registers and
	 * the JTAG (?) tap registers, which are located in address 0x4A00_2200 to
	 * 0x4A00_2218.  This is part of the L4_CORE memory range and should have
	 * been mapped in by the machdep.c code.
	 *
	 *   STD_FUSE_DIE_ID_0    0x4A00 2200
	 *   ID_CODE              0x4A00 2204   (this is the only one we need)
	 *   STD_FUSE_DIE_ID_1    0x4A00 2208
	 *   STD_FUSE_DIE_ID_2    0x4A00 220C
	 *   STD_FUSE_DIE_ID_3    0x4A00 2210
	 *   STD_FUSE_PROD_ID_0   0x4A00 2214
	 *   STD_FUSE_PROD_ID_1   0x4A00 2218
	 */
	/* FIXME Should we map somewhere else? */
	bus_space_map(fdtbus_bs_tag,OMAP44XX_L4_CORE_HWBASE, 0x4000, 0, &bsh);
	id_code = bus_space_read_4(fdtbus_bs_tag, bsh, OMAP4_ID_CODE);
	bus_space_unmap(fdtbus_bs_tag, bsh, 0x4000);

	hawkeye = ((id_code >> 12) & 0xffff);
	revision = ((id_code >> 28) & 0xf);

	/* Apparently according to the linux code there were some ES2.0 samples that
	 * have the wrong id code and report themselves as ES1.0 silicon.  So used
	 * the ARM cpuid to get the correct revision.
	 */
	if (revision == 0) {
		id_code = cp15_midr_get();
		revision = (id_code & 0xf) - 1;
	}

	switch (hawkeye) {
	case 0xB852:
		switch (revision) {
		case 0:
			chip_revision = OMAP4430_REV_ES1_0;
			break;
		case 1:
			chip_revision = OMAP4430_REV_ES2_1;
			break;
		default:
			chip_revision = OMAP4430_REV_UNKNOWN;
			break;
		}
		break;

	case 0xB95C:
		switch (revision) {
		case 3:
			chip_revision = OMAP4430_REV_ES2_1;
			break;
		case 4:
			chip_revision = OMAP4430_REV_ES2_2;
			break;
		case 6:
			chip_revision = OMAP4430_REV_ES2_3;
			break;
		default:
			chip_revision = OMAP4430_REV_UNKNOWN;
			break;
		}
		break;

	case 0xB94E:
		switch (revision) {
		case 0:
			chip_revision = OMAP4460_REV_ES1_0;
			break;
		case 2:
			chip_revision = OMAP4460_REV_ES1_1;
			break;
		default:
			chip_revision = OMAP4460_REV_UNKNOWN;
			break;
		}
		break;

	case 0xB975:
		switch (revision) {
		case 0:
			chip_revision = OMAP4470_REV_ES1_0;
			break;
		default:
			chip_revision = OMAP4470_REV_UNKNOWN;
			break;
		}
		break;

	default:
		/* Default to the latest revision if we can't determine type */
		chip_revision = OMAP_UNKNOWN_DEV;
		break;
	}
	if (chip_revision != OMAP_UNKNOWN_DEV) {
		printf("Texas Instruments OMAP%04x Processor, Revision ES%u.%u\n",
		    OMAP_REV_DEVICE(chip_revision), OMAP_REV_MAJOR(chip_revision), 
		    OMAP_REV_MINOR(chip_revision));
	}
	else {
		printf("Texas Instruments unknown OMAP chip: %04x, rev %d\n",
		    hawkeye, revision); 
	}
}