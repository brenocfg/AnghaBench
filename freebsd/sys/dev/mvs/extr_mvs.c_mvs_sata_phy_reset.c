#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mvs_channel {scalar_t__ pm_level; int /*<<< orphan*/  r_mem; scalar_t__ pm_present; TYPE_1__* user; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SATA_SC ; 
 int SATA_SC_DET_DISABLE ; 
 int SATA_SC_DET_IDLE ; 
 int SATA_SC_DET_RESET ; 
 int SATA_SC_IPM_DIS_PARTIAL ; 
 int SATA_SC_IPM_DIS_SLUMBER ; 
 int SATA_SC_SPD_SPEED_GEN1 ; 
 int SATA_SC_SPD_SPEED_GEN2 ; 
 int SATA_SC_SPD_SPEED_GEN3 ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_sata_connect (struct mvs_channel*) ; 

__attribute__((used)) static int
mvs_sata_phy_reset(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	int sata_rev;
	uint32_t val;

	sata_rev = ch->user[ch->pm_present ? 15 : 0].revision;
	if (sata_rev == 1)
		val = SATA_SC_SPD_SPEED_GEN1;
	else if (sata_rev == 2)
		val = SATA_SC_SPD_SPEED_GEN2;
	else if (sata_rev == 3)
		val = SATA_SC_SPD_SPEED_GEN3;
	else
		val = 0;
	ATA_OUTL(ch->r_mem, SATA_SC,
	    SATA_SC_DET_RESET | val |
	    SATA_SC_IPM_DIS_PARTIAL | SATA_SC_IPM_DIS_SLUMBER);
	DELAY(1000);
	ATA_OUTL(ch->r_mem, SATA_SC,
	    SATA_SC_DET_IDLE | val | ((ch->pm_level > 0) ? 0 :
	    (SATA_SC_IPM_DIS_PARTIAL | SATA_SC_IPM_DIS_SLUMBER)));
	if (!mvs_sata_connect(ch)) {
		if (ch->pm_level > 0)
			ATA_OUTL(ch->r_mem, SATA_SC, SATA_SC_DET_DISABLE);
		return (0);
	}
	return (1);
}