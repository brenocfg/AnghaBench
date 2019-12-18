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
typedef  int /*<<< orphan*/  uint32_t ;
struct mvs_channel {scalar_t__ numrslots; int pm_level; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SATA_SC ; 
 int /*<<< orphan*/  SATA_SC_SPM_MASK ; 
 int /*<<< orphan*/  SATA_SC_SPM_PARTIAL ; 
 int /*<<< orphan*/  SATA_SC_SPM_SLUMBER ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_ch_pm(void *arg)
{
	device_t dev = (device_t)arg;
	struct mvs_channel *ch = device_get_softc(dev);
	uint32_t work;

	if (ch->numrslots != 0)
		return;
	/* If we are idle - request power state transition. */
	work = ATA_INL(ch->r_mem, SATA_SC);
	work &= ~SATA_SC_SPM_MASK;
	if (ch->pm_level == 4)
		work |= SATA_SC_SPM_PARTIAL;
	else
		work |= SATA_SC_SPM_SLUMBER;
	ATA_OUTL(ch->r_mem, SATA_SC, work);
}