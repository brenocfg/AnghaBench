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
typedef  int u32 ;
struct TYPE_2__ {int serror; } ;
struct ata_eh_context {TYPE_1__ i; } ;
struct ata_link {struct ata_eh_context eh_context; } ;
typedef  enum ata_lpm_policy { ____Placeholder_ata_lpm_policy } ata_lpm_policy ;

/* Variables and functions */
#define  ATA_LPM_MAX_POWER 132 
#define  ATA_LPM_MED_POWER 131 
#define  ATA_LPM_MED_POWER_WITH_DIPM 130 
#define  ATA_LPM_MIN_POWER 129 
#define  ATA_LPM_MIN_POWER_WITH_PARTIAL 128 
 int /*<<< orphan*/  SCR_CONTROL ; 
 int /*<<< orphan*/  SCR_ERROR ; 
 int SERR_PHYRDY_CHG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_link_nr_enabled (struct ata_link*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int sata_scr_write (struct ata_link*,int /*<<< orphan*/ ,int) ; 

int sata_link_scr_lpm(struct ata_link *link, enum ata_lpm_policy policy,
		      bool spm_wakeup)
{
	struct ata_eh_context *ehc = &link->eh_context;
	bool woken_up = false;
	u32 scontrol;
	int rc;

	rc = sata_scr_read(link, SCR_CONTROL, &scontrol);
	if (rc)
		return rc;

	switch (policy) {
	case ATA_LPM_MAX_POWER:
		/* disable all LPM transitions */
		scontrol |= (0x7 << 8);
		/* initiate transition to active state */
		if (spm_wakeup) {
			scontrol |= (0x4 << 12);
			woken_up = true;
		}
		break;
	case ATA_LPM_MED_POWER:
		/* allow LPM to PARTIAL */
		scontrol &= ~(0x1 << 8);
		scontrol |= (0x6 << 8);
		break;
	case ATA_LPM_MED_POWER_WITH_DIPM:
	case ATA_LPM_MIN_POWER_WITH_PARTIAL:
	case ATA_LPM_MIN_POWER:
		if (ata_link_nr_enabled(link) > 0)
			/* no restrictions on LPM transitions */
			scontrol &= ~(0x7 << 8);
		else {
			/* empty port, power off */
			scontrol &= ~0xf;
			scontrol |= (0x1 << 2);
		}
		break;
	default:
		WARN_ON(1);
	}

	rc = sata_scr_write(link, SCR_CONTROL, scontrol);
	if (rc)
		return rc;

	/* give the link time to transit out of LPM state */
	if (woken_up)
		msleep(10);

	/* clear PHYRDY_CHG from SError */
	ehc->i.serror &= ~SERR_PHYRDY_CHG;
	return sata_scr_write(link, SCR_ERROR, SERR_PHYRDY_CHG);
}