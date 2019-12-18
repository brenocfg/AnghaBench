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
struct siis_channel {int /*<<< orphan*/  r_mem; scalar_t__ pm_present; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIIS_P_CTLCLR ; 
 int /*<<< orphan*/  SIIS_P_CTLSET ; 
 int /*<<< orphan*/  SIIS_P_CTL_32BIT ; 
 int /*<<< orphan*/  SIIS_P_CTL_PME ; 
 int /*<<< orphan*/  SIIS_P_CTL_PORT_RESET ; 
 int /*<<< orphan*/  SIIS_P_IESET ; 
 int /*<<< orphan*/  SIIS_P_IX_ENABLED ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siis_ch_init(device_t dev)
{
	struct siis_channel *ch = device_get_softc(dev);

	/* Get port out of reset state. */
	ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_PORT_RESET);
	ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_32BIT);
	if (ch->pm_present)
		ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_PME);
	else
		ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_PME);
	/* Enable port interrupts */
	ATA_OUTL(ch->r_mem, SIIS_P_IESET, SIIS_P_IX_ENABLED);
	return (0);
}