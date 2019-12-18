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
typedef  int u_int ;
struct ahc_softc {int chip; int pause; int features; int (* bus_chip_init ) (struct ahc_softc*) ;} ;

/* Variables and functions */
 int AHC_AIC7770 ; 
 int AHC_CHIPID_MASK ; 
 int AHC_PCI ; 
 int AHC_TWIN ; 
 int AHC_WIDE ; 
 int CHIPRST ; 
 int CHIPRSTACK ; 
 int /*<<< orphan*/  HCNTRL ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int SELBUSB ; 
 int SELWIDE ; 
 int /*<<< orphan*/  SXFRCTL1 ; 
 int /*<<< orphan*/  ahc_dumpseq (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  aic_delay (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stub1 (struct ahc_softc*) ; 

int
ahc_reset(struct ahc_softc *ahc, int reinit)
{
	u_int	sblkctl;
	u_int	sxfrctl1_a, sxfrctl1_b;
	int	error;
	int	wait;
	
	/*
	 * Preserve the value of the SXFRCTL1 register for all channels.
	 * It contains settings that affect termination and we don't want
	 * to disturb the integrity of the bus.
	 */
	ahc_pause(ahc);
	sxfrctl1_b = 0;
	if ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7770) {
		u_int sblkctl;

		/*
		 * Save channel B's settings in case this chip
		 * is setup for TWIN channel operation.
		 */
		sblkctl = ahc_inb(ahc, SBLKCTL);
		ahc_outb(ahc, SBLKCTL, sblkctl | SELBUSB);
		sxfrctl1_b = ahc_inb(ahc, SXFRCTL1);
		ahc_outb(ahc, SBLKCTL, sblkctl & ~SELBUSB);
	}
	sxfrctl1_a = ahc_inb(ahc, SXFRCTL1);

	ahc_outb(ahc, HCNTRL, CHIPRST | ahc->pause);

	/*
	 * Ensure that the reset has finished.  We delay 1000us
	 * prior to reading the register to make sure the chip
	 * has sufficiently completed its reset to handle register
	 * accesses.
	 */
	wait = 1000;
	do {
		aic_delay(1000);
	} while (--wait && !(ahc_inb(ahc, HCNTRL) & CHIPRSTACK));

	if (wait == 0) {
		printf("%s: WARNING - Failed chip reset!  "
		       "Trying to initialize anyway.\n", ahc_name(ahc));
	}
	ahc_outb(ahc, HCNTRL, ahc->pause);

	/* Determine channel configuration */
	sblkctl = ahc_inb(ahc, SBLKCTL) & (SELBUSB|SELWIDE);
	/* No Twin Channel PCI cards */
	if ((ahc->chip & AHC_PCI) != 0)
		sblkctl &= ~SELBUSB;
	switch (sblkctl) {
	case 0:
		/* Single Narrow Channel */
		break;
	case 2:
		/* Wide Channel */
		ahc->features |= AHC_WIDE;
		break;
	case 8:
		/* Twin Channel */
		ahc->features |= AHC_TWIN;
		break;
	default:
		printf(" Unsupported adapter type.  Ignoring\n");
		return(-1);
	}

	/*
	 * Reload sxfrctl1.
	 *
	 * We must always initialize STPWEN to 1 before we
	 * restore the saved values.  STPWEN is initialized
	 * to a tri-state condition which can only be cleared
	 * by turning it on.
	 */
	if ((ahc->features & AHC_TWIN) != 0) {
		u_int sblkctl;

		sblkctl = ahc_inb(ahc, SBLKCTL);
		ahc_outb(ahc, SBLKCTL, sblkctl | SELBUSB);
		ahc_outb(ahc, SXFRCTL1, sxfrctl1_b);
		ahc_outb(ahc, SBLKCTL, sblkctl & ~SELBUSB);
	}
	ahc_outb(ahc, SXFRCTL1, sxfrctl1_a);

	error = 0;
	if (reinit != 0)
		/*
		 * If a recovery action has forced a chip reset,
		 * re-initialize the chip to our liking.
		 */
		error = ahc->bus_chip_init(ahc);
#ifdef AHC_DUMP_SEQ
	else 
		ahc_dumpseq(ahc);
#endif

	return (error);
}