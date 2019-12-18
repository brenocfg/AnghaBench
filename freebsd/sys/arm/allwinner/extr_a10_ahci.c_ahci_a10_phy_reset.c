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
struct ahci_controller {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_PHYCS0R ; 
 int /*<<< orphan*/  AHCI_PHYCS1R ; 
 int /*<<< orphan*/  AHCI_PHYCS2R ; 
 int /*<<< orphan*/  AHCI_RWCR ; 
 scalar_t__ ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PHYCS0R_BIT18 ; 
 int PHYCS0R_BIT23 ; 
 scalar_t__ PHYCS0R_POWER_ENABLE ; 
 scalar_t__ PHYCS0R_POWER_STATUS_MASK ; 
 scalar_t__ PHYCS0R_PS_GOOD ; 
 int PHYCS0R_UF1_INIT ; 
 int PHYCS0R_UF1_MASK ; 
 int PHYCS0R_UF2_INIT ; 
 int PHYCS0R_UF2_MASK ; 
 scalar_t__ PHYCS1R_BIT15 ; 
 scalar_t__ PHYCS1R_BIT28 ; 
 scalar_t__ PHYCS1R_HIGHZ ; 
 int PHYCS1R_UF1_INIT ; 
 int PHYCS1R_UF1_MASK ; 
 int PHYCS1R_UF2_INIT ; 
 int PHYCS1R_UF2_MASK ; 
 int PHYCS1R_UF3_INIT ; 
 int PHYCS1R_UF3_MASK ; 
 scalar_t__ PHYCS2R_CALIBRATE ; 
 int PHYCS2R_UF1_INIT ; 
 int PHYCS2R_UF1_MASK ; 
 scalar_t__ PHY_RESET_TIMEOUT ; 
 int /*<<< orphan*/  ahci_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ahci_mask_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ahci_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bootverbose ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
ahci_a10_phy_reset(device_t dev)
{
	uint32_t to, val;
	struct ahci_controller *ctlr = device_get_softc(dev);

	/*
	 * Here starts the magic -- most of the comments are based
	 * on guesswork, names of routines and printf error
	 * messages.  The code works, but it will do that even if the
	 * comments are 100% BS.
	 */

	/*
	 * Lock out other access while we initialize.  Or at least that
	 * seems to be the case based on Linux SDK #defines.  Maybe this
	 * put things into reset?
	 */
	ATA_OUTL(ctlr->r_mem, AHCI_RWCR, 0);
	DELAY(100);

	/*
	 * Set bit 19 in PHYCS1R.  Guessing this disables driving the PHY
	 * port for a bit while we reset things.
	 */
	ahci_set(ctlr->r_mem, AHCI_PHYCS1R, PHYCS1R_HIGHZ);

	/*
	 * Frob PHYCS0R...
	 */
	ahci_mask_set(ctlr->r_mem, AHCI_PHYCS0R,
	    ~PHYCS0R_UF2_MASK,
	    PHYCS0R_UF2_INIT | PHYCS0R_BIT23 | PHYCS0R_BIT18);

	/*
	 * Set three fields in PHYCS1R
	 */
	ahci_mask_set(ctlr->r_mem, AHCI_PHYCS1R,
	    ~(PHYCS1R_UF1_MASK | PHYCS1R_UF2_MASK | PHYCS1R_UF3_MASK),
	    PHYCS1R_UF1_INIT | PHYCS1R_UF2_INIT | PHYCS1R_UF3_INIT);

	/*
	 * Two more mystery bits in PHYCS1R. -- can these be combined above?
	 */
	ahci_set(ctlr->r_mem, AHCI_PHYCS1R, PHYCS1R_BIT15 | PHYCS1R_BIT28);

	/*
	 * Now clear that first mysery bit.  Perhaps this starts
	 * driving the PHY again so we can power it up and start
	 * talking to the SATA drive, if any below.
	 */
	ahci_clr(ctlr->r_mem, AHCI_PHYCS1R, PHYCS1R_HIGHZ);

	/*
	 * Frob PHYCS0R again...
	 */
	ahci_mask_set(ctlr->r_mem, AHCI_PHYCS0R,
	    ~PHYCS0R_UF1_MASK, PHYCS0R_UF1_INIT);

	/*
	 * Frob PHYCS2R, because 25 means something?
	 */
	ahci_mask_set(ctlr->r_mem, AHCI_PHYCS2R, ~PHYCS2R_UF1_MASK,
	    PHYCS2R_UF1_INIT);

	DELAY(100);		/* WAG */

	/*
	 * Turn on the power to the PHY and wait for it to report back
	 * good?
	 */
	ahci_set(ctlr->r_mem, AHCI_PHYCS0R, PHYCS0R_POWER_ENABLE);
	for (to = PHY_RESET_TIMEOUT; to > 0; to--) {
		val = ATA_INL(ctlr->r_mem, AHCI_PHYCS0R);
		if ((val & PHYCS0R_POWER_STATUS_MASK) == PHYCS0R_PS_GOOD)
			break;
		DELAY(10);
	}
	if (to == 0 && bootverbose)
		device_printf(dev, "PHY Power Failed PHYCS0R = %#x\n", val);

	/*
	 * Calibrate the clocks between the device and the host.  This appears
	 * to be an automated process that clears the bit when it is done.
	 */
	ahci_set(ctlr->r_mem, AHCI_PHYCS2R, PHYCS2R_CALIBRATE);
	for (to = PHY_RESET_TIMEOUT; to > 0; to--) {
		val = ATA_INL(ctlr->r_mem, AHCI_PHYCS2R);
		if ((val & PHYCS2R_CALIBRATE) == 0)
			break;
		DELAY(10);
	}
	if (to == 0 && bootverbose)
		device_printf(dev, "PHY Cal Failed PHYCS2R %#x\n", val);

	/*
	 * OK, let things settle down a bit.
	 */
	DELAY(1000);

	/*
	 * Go back into normal mode now that we've calibrated the PHY.
	 */
	ATA_OUTL(ctlr->r_mem, AHCI_RWCR, 7);
}