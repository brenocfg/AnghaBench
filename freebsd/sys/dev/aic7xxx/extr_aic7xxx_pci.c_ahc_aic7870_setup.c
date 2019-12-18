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
struct ahc_softc {char channel; int bugs; int instruction_ram_size; int /*<<< orphan*/  features; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_AIC7870 ; 
 int /*<<< orphan*/  AHC_AIC7870_FE ; 
 int AHC_CACHETHEN_BUG ; 
 int AHC_PCI_MWI_BUG ; 
 int AHC_TMODE_WIDEODD_BUG ; 

__attribute__((used)) static int
ahc_aic7870_setup(struct ahc_softc *ahc)
{

	ahc->channel = 'A';
	ahc->chip = AHC_AIC7870;
	ahc->features = AHC_AIC7870_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG|AHC_CACHETHEN_BUG|AHC_PCI_MWI_BUG;
	ahc->instruction_ram_size = 512;
	return (0);
}