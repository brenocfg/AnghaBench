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
typedef  int uint8_t ;
struct exca_softc {int /*<<< orphan*/  chipset; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EXCA_BOGUS ; 
 int /*<<< orphan*/  EXCA_CIRRUS_CHIP_INFO ; 
 int EXCA_CIRRUS_CHIP_INFO_CHIP_ID ; 
 int EXCA_CIRRUS_CHIP_INFO_SLOTS ; 
 int /*<<< orphan*/  EXCA_I82365 ; 
 int /*<<< orphan*/  EXCA_I82365SL_DF ; 
 int /*<<< orphan*/  EXCA_IBM ; 
 int /*<<< orphan*/  EXCA_IBM_KING ; 
 int /*<<< orphan*/  EXCA_IDENT ; 
 int EXCA_IDENT_IFTYPE_MASK ; 
 int EXCA_IDENT_IFTYPE_MEM_AND_IO ; 
#define  EXCA_IDENT_REV_I82365SLDF 133 
#define  EXCA_IDENT_REV_I82365SLR0 132 
#define  EXCA_IDENT_REV_I82365SLR1 131 
#define  EXCA_IDENT_REV_IBM1 130 
#define  EXCA_IDENT_REV_IBM2 129 
#define  EXCA_IDENT_REV_IBM_KING 128 
 int EXCA_IDENT_REV_MASK ; 
 int EXCA_IDENT_ZERO ; 
 int /*<<< orphan*/  EXCA_PD6710 ; 
 int /*<<< orphan*/  EXCA_PD6722 ; 
 int /*<<< orphan*/  EXCA_REG_INDEX ; 
 int /*<<< orphan*/  EXCA_RF5C296 ; 
 int /*<<< orphan*/  EXCA_RF5C396 ; 
 int /*<<< orphan*/  EXCA_RICOH_ID ; 
 int EXCA_RID_296 ; 
 int EXCA_RID_396 ; 
 int /*<<< orphan*/  EXCA_VADEM_COOKIE1 ; 
 int /*<<< orphan*/  EXCA_VADEM_COOKIE2 ; 
 int /*<<< orphan*/  EXCA_VADEM_REV ; 
 int /*<<< orphan*/  EXCA_VADEM_VMISC ; 
 int /*<<< orphan*/  EXCA_VG365 ; 
 int /*<<< orphan*/  EXCA_VG465 ; 
 int /*<<< orphan*/  EXCA_VG468 ; 
 int /*<<< orphan*/  EXCA_VG469 ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_clrb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int exca_getb (struct exca_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_putb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_setb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exca_valid_slot(struct exca_softc *exca)
{
	uint8_t c;

	/* Assume the worst */
	exca->chipset = EXCA_BOGUS;

	/*
	 * see if there's a PCMCIA controller here
	 * Intel PCMCIA controllers use 0x82 and 0x83
	 * IBM clone chips use 0x88 and 0x89, apparently
	 */
	c = exca_getb(exca, EXCA_IDENT);
	DEVPRINTF(exca->dev, "Ident is %x\n", c);
	if ((c & EXCA_IDENT_IFTYPE_MASK) != EXCA_IDENT_IFTYPE_MEM_AND_IO)
		return (0);
	if ((c & EXCA_IDENT_ZERO) != 0)
		return (0);
	switch (c & EXCA_IDENT_REV_MASK) {
	/*
	 *	82365 or clones.
	 */
	case EXCA_IDENT_REV_I82365SLR0:
	case EXCA_IDENT_REV_I82365SLR1:
		exca->chipset = EXCA_I82365;
		/*
		 * Check for Vadem chips by unlocking their extra
		 * registers and looking for valid ID.  Bit 3 in
		 * the ID register is normally 0, except when
		 * EXCA_VADEMREV is set.  Other bridges appear
		 * to ignore this frobbing.
		 */
		bus_space_write_1(exca->bst, exca->bsh, EXCA_REG_INDEX,
		    EXCA_VADEM_COOKIE1);
		bus_space_write_1(exca->bst, exca->bsh, EXCA_REG_INDEX,
		    EXCA_VADEM_COOKIE2);
		exca_setb(exca, EXCA_VADEM_VMISC, EXCA_VADEM_REV);
		c = exca_getb(exca, EXCA_IDENT);
		if (c & 0x08) {
			switch (c & 7) {
			case 1:
				exca->chipset = EXCA_VG365;
				break;
			case 2:
				exca->chipset = EXCA_VG465;
				break;
			case 3:
				exca->chipset = EXCA_VG468;
				break;
			default:
				exca->chipset = EXCA_VG469;
				break;
			}
			exca_clrb(exca, EXCA_VADEM_VMISC, EXCA_VADEM_REV);
			break;
		}
		/*
		 * Check for RICOH RF5C[23]96 PCMCIA Controller
		 */
		c = exca_getb(exca, EXCA_RICOH_ID);
		if (c == EXCA_RID_396) {
			exca->chipset = EXCA_RF5C396;
			break;
		} else if (c == EXCA_RID_296) {
			exca->chipset = EXCA_RF5C296;
			break;
		}
		/*
		 *	Check for Cirrus logic chips.
		 */
		exca_putb(exca, EXCA_CIRRUS_CHIP_INFO, 0);
		c = exca_getb(exca, EXCA_CIRRUS_CHIP_INFO);
		if ((c & EXCA_CIRRUS_CHIP_INFO_CHIP_ID) ==
		    EXCA_CIRRUS_CHIP_INFO_CHIP_ID) {
			c = exca_getb(exca, EXCA_CIRRUS_CHIP_INFO);
			if ((c & EXCA_CIRRUS_CHIP_INFO_CHIP_ID) == 0) {
				if (c & EXCA_CIRRUS_CHIP_INFO_SLOTS)
					exca->chipset = EXCA_PD6722;
				else
					exca->chipset = EXCA_PD6710;
				break;
			}
		}
		break;

	case EXCA_IDENT_REV_I82365SLDF:
		/*
		 *	Intel i82365sl-DF step or maybe a vlsi 82c146
		 * we detected the vlsi case earlier, so if the controller
		 * isn't set, we know it is a i82365sl step D.
		 */
		exca->chipset = EXCA_I82365SL_DF;
		break;
	case EXCA_IDENT_REV_IBM1:
	case EXCA_IDENT_REV_IBM2:
		exca->chipset = EXCA_IBM;
		break;
	case EXCA_IDENT_REV_IBM_KING:
		exca->chipset = EXCA_IBM_KING;
		break;
	default:
		return (0);
	}
	return (1);
}