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
typedef  int uint16_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CARDBUS_EXROM_DATA_IMAGE_LENGTH ; 
 int CARDBUS_EXROM_DATA_INDICATOR ; 
 int CARDBUS_EXROM_DATA_PTR ; 
 int CARDBUS_EXROM_SIGNATURE ; 
 struct resource* CIS_CONFIG_SPACE ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int PCIM_CIS_ADDR_MASK ; 
#define  PCIM_CIS_ASI_BAR0 135 
#define  PCIM_CIS_ASI_BAR1 134 
#define  PCIM_CIS_ASI_BAR2 133 
#define  PCIM_CIS_ASI_BAR3 132 
#define  PCIM_CIS_ASI_BAR4 131 
#define  PCIM_CIS_ASI_BAR5 130 
#define  PCIM_CIS_ASI_CONFIG 129 
 int PCIM_CIS_ASI_MASK ; 
#define  PCIM_CIS_ASI_ROM 128 
 int PCIM_CIS_ROM_MASK ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int PCIR_BIOS ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_read_1 (struct resource*,int) ; 
 int bus_read_2 (struct resource*,int) ; 
 int /*<<< orphan*/  cardbus_read_tuple_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int rman_make_alignment_flags (int) ; 

__attribute__((used)) static struct resource *
cardbus_read_tuple_init(device_t cbdev, device_t child, uint32_t *start,
    int *rid)
{
	struct resource *res;
	uint32_t space;

	space = *start & PCIM_CIS_ASI_MASK;
	switch (space) {
	case PCIM_CIS_ASI_CONFIG:
		DEVPRINTF((cbdev, "CIS in PCI config space\n"));
		/* CIS in PCI config space need no initialization */
		return (CIS_CONFIG_SPACE);
	case PCIM_CIS_ASI_BAR0:
	case PCIM_CIS_ASI_BAR1:
	case PCIM_CIS_ASI_BAR2:
	case PCIM_CIS_ASI_BAR3:
	case PCIM_CIS_ASI_BAR4:
	case PCIM_CIS_ASI_BAR5:
		*rid = PCIR_BAR(space - PCIM_CIS_ASI_BAR0);
		DEVPRINTF((cbdev, "CIS in BAR %#x\n", *rid));
		break;
	case PCIM_CIS_ASI_ROM:
		*rid = PCIR_BIOS;
		DEVPRINTF((cbdev, "CIS in option rom\n"));
		break;
	default:
		device_printf(cbdev, "Unable to read CIS: Unknown space: %d\n",
		    space);
		return (NULL);
	}

	/* allocate the memory space to read CIS */
	res = bus_alloc_resource_any(child, SYS_RES_MEMORY, rid,
	    rman_make_alignment_flags(4096) | RF_ACTIVE);
	if (res == NULL) {
		device_printf(cbdev, "Unable to allocate resource "
		    "to read CIS.\n");
		return (NULL);
	}
	DEVPRINTF((cbdev, "CIS Mapped to %#jx\n",
	    rman_get_start(res)));

	/* Flip to the right ROM image if CIS is in ROM */
	if (space == PCIM_CIS_ASI_ROM) {
		uint32_t imagesize;
		uint32_t imagebase = 0;
		uint32_t pcidata;
		uint16_t romsig;
		int romnum = 0;
		int imagenum;

		imagenum = (*start & PCIM_CIS_ROM_MASK) >> 28;
		for (romnum = 0;; romnum++) {
			romsig = bus_read_2(res,
			    imagebase + CARDBUS_EXROM_SIGNATURE);
			if (romsig != 0xaa55) {
				device_printf(cbdev, "Bad header in rom %d: "
				    "[%x] %04x\n", romnum, imagebase +
				    CARDBUS_EXROM_SIGNATURE, romsig);
				cardbus_read_tuple_finish(cbdev, child, *rid,
				    res);
				*rid = 0;
				return (NULL);
			}

			/*
			 * If this was the Option ROM image that we were
			 * looking for, then we are done.
			 */
			if (romnum == imagenum)
				break;

			/* Find out where the next Option ROM image is */
			pcidata = imagebase + bus_read_2(res,
			    imagebase + CARDBUS_EXROM_DATA_PTR);
			imagesize = bus_read_2(res,
			    pcidata + CARDBUS_EXROM_DATA_IMAGE_LENGTH);

			if (imagesize == 0) {
				/*
				 * XXX some ROMs seem to have this as zero,
				 * can we assume this means 1 block?
				 */
				device_printf(cbdev, "Warning, size of Option "
				    "ROM image %d is 0 bytes, assuming 512 "
				    "bytes.\n", romnum);
				imagesize = 1;
			}

			/* Image size is in 512 byte units */
			imagesize <<= 9;

			if ((bus_read_1(res, pcidata +
			    CARDBUS_EXROM_DATA_INDICATOR) & 0x80) != 0) {
				device_printf(cbdev, "Cannot find CIS in "
				    "Option ROM\n");
				cardbus_read_tuple_finish(cbdev, child, *rid,
				    res);
				*rid = 0;
				return (NULL);
			}
			imagebase += imagesize;
		}
		*start = imagebase + (*start & PCIM_CIS_ADDR_MASK);
	} else {
		*start = *start & PCIM_CIS_ADDR_MASK;
	}
	DEVPRINTF((cbdev, "CIS offset is %#x\n", *start));

	return (res);
}