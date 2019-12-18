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
typedef  int u_int32_t ;
struct ahci_channel {int chcaps; int fbs_enabled; scalar_t__ pm_present; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  (* start ) (struct ahci_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int AHCI_P_CMD_FBSCP ; 
 int AHCI_P_CMD_PMA ; 
 int AHCI_P_CMD_ST ; 
 int /*<<< orphan*/  AHCI_P_FBS ; 
 int AHCI_P_FBS_EN ; 
 int /*<<< orphan*/  AHCI_P_IS ; 
 int /*<<< orphan*/  AHCI_P_SERR ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ahci_channel*) ; 

__attribute__((used)) static void
ahci_start(struct ahci_channel *ch, int fbs)
{
	u_int32_t cmd;

	/* Run the channel start callback, if any. */
	if (ch->start)
		ch->start(ch);

	/* Clear SATA error register */
	ATA_OUTL(ch->r_mem, AHCI_P_SERR, 0xFFFFFFFF);
	/* Clear any interrupts pending on this channel */
	ATA_OUTL(ch->r_mem, AHCI_P_IS, 0xFFFFFFFF);
	/* Configure FIS-based switching if supported. */
	if (ch->chcaps & AHCI_P_CMD_FBSCP) {
		ch->fbs_enabled = (fbs && ch->pm_present) ? 1 : 0;
		ATA_OUTL(ch->r_mem, AHCI_P_FBS,
		    ch->fbs_enabled ? AHCI_P_FBS_EN : 0);
	}
	/* Start operations on this channel */
	cmd = ATA_INL(ch->r_mem, AHCI_P_CMD);
	cmd &= ~AHCI_P_CMD_PMA;
	ATA_OUTL(ch->r_mem, AHCI_P_CMD, cmd | AHCI_P_CMD_ST |
	    (ch->pm_present ? AHCI_P_CMD_PMA : 0));
}