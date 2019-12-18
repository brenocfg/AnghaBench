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
struct mvs_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SATA_SC ; 
 int SATA_SC_SPM_ACTIVE ; 
 int SATA_SC_SPM_MASK ; 
 int /*<<< orphan*/  SATA_SS ; 
 int SATA_SS_IPM_ACTIVE ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_ch_pm_wake(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	uint32_t work;
	int timeout = 0;

	work = ATA_INL(ch->r_mem, SATA_SS);
	if (work & SATA_SS_IPM_ACTIVE)
		return;
	/* If we are not in active state - request power state transition. */
	work = ATA_INL(ch->r_mem, SATA_SC);
	work &= ~SATA_SC_SPM_MASK;
	work |= SATA_SC_SPM_ACTIVE;
	ATA_OUTL(ch->r_mem, SATA_SC, work);
	/* Wait for transition to happen. */
	while ((ATA_INL(ch->r_mem, SATA_SS) & SATA_SS_IPM_ACTIVE) == 0 &&
	    timeout++ < 100) {
		DELAY(100);
	}
}