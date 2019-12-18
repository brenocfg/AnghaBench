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
struct ahc_softc {char channel; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev_softc; } ;
typedef  int /*<<< orphan*/  aic_dev_softc_t ;

/* Variables and functions */
#define  AHC_398X_SLOT_CHANNEL_A 130 
#define  AHC_398X_SLOT_CHANNEL_B 129 
#define  AHC_398X_SLOT_CHANNEL_C 128 
 int /*<<< orphan*/  AHC_LARGE_SEEPROM ; 
 int aic_get_pci_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
ahc_aha398XX_setup(struct ahc_softc *ahc)
{
	aic_dev_softc_t pci;

	pci = ahc->dev_softc;
	switch (aic_get_pci_slot(pci)) {
	case AHC_398X_SLOT_CHANNEL_A:
		ahc->channel = 'A';
		break;
	case AHC_398X_SLOT_CHANNEL_B:
		ahc->channel = 'B';
		break;
	case AHC_398X_SLOT_CHANNEL_C:
		ahc->channel = 'C';
		break;
	default:
		printf("adapter at unexpected slot %d\n"
		       "unable to map to a channel\n",
		       aic_get_pci_slot(pci));
		ahc->channel = 'A';
		break;
	}
	ahc->flags |= AHC_LARGE_SEEPROM;
	return (0);
}