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
struct ahci_channel {int caps; int /*<<< orphan*/  dev; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int AHCI_CAP_SCLO ; 
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int AHCI_P_CMD_CLO ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ahci_clo(struct ahci_channel *ch)
{
	u_int32_t cmd;
	int timeout;

	/* Issue Command List Override if supported */ 
	if (ch->caps & AHCI_CAP_SCLO) {
		cmd = ATA_INL(ch->r_mem, AHCI_P_CMD);
		cmd |= AHCI_P_CMD_CLO;
		ATA_OUTL(ch->r_mem, AHCI_P_CMD, cmd);
		timeout = 0;
		do {
			DELAY(10);
			if (timeout++ > 50000) {
			    device_printf(ch->dev, "executing CLO failed\n");
			    break;
			}
		} while (ATA_INL(ch->r_mem, AHCI_P_CMD) & AHCI_P_CMD_CLO);
	}
}