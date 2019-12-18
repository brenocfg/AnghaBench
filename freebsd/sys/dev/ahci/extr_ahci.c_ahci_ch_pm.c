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
struct ahci_channel {scalar_t__ numrslots; int pm_level; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int /*<<< orphan*/  AHCI_P_CMD_PARTIAL ; 
 int /*<<< orphan*/  AHCI_P_CMD_SLUMBER ; 
 int /*<<< orphan*/  ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_ch_pm(void *arg)
{
	struct ahci_channel *ch = (struct ahci_channel *)arg;
	uint32_t work;

	if (ch->numrslots != 0)
		return;
	work = ATA_INL(ch->r_mem, AHCI_P_CMD);
	if (ch->pm_level == 4)
		work |= AHCI_P_CMD_PARTIAL;
	else
		work |= AHCI_P_CMD_SLUMBER;
	ATA_OUTL(ch->r_mem, AHCI_P_CMD, work);
}