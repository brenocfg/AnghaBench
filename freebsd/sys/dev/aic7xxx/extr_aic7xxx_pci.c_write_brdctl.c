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
struct ahc_softc {int chip; char channel; int features; } ;

/* Variables and functions */
 int AHC_AIC7895 ; 
 int AHC_CHIPID_MASK ; 
 int AHC_ULTRA2 ; 
 int BRDCS ; 
 int /*<<< orphan*/  BRDCTL ; 
 int BRDSTB ; 
 int BRDSTB_ULTRA2 ; 
 int /*<<< orphan*/  ahc_flush_device_writes (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
write_brdctl(struct ahc_softc *ahc, uint8_t value)
{
	uint8_t brdctl;

	if ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7895) {
		brdctl = BRDSTB;
	 	if (ahc->channel == 'B')
			brdctl |= BRDCS;
	} else if ((ahc->features & AHC_ULTRA2) != 0) {
		brdctl = 0;
	} else {
		brdctl = BRDSTB|BRDCS;
	}
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	brdctl |= value;
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	if ((ahc->features & AHC_ULTRA2) != 0)
		brdctl |= BRDSTB_ULTRA2;
	else
		brdctl &= ~BRDSTB;
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	if ((ahc->features & AHC_ULTRA2) != 0)
		brdctl = 0;
	else
		brdctl &= ~BRDCS;
	ahc_outb(ahc, BRDCTL, brdctl);
}