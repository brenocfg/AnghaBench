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
struct ahci_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int /*<<< orphan*/  AHCI_P_CMD_SLUMBER ; 
 int /*<<< orphan*/  AHCI_P_IE ; 
 int /*<<< orphan*/  AHCI_P_SCTL ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_SC_DET_DISABLE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ahci_stop (struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_stop_fr (struct ahci_channel*) ; 
 struct ahci_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahci_ch_deinit(device_t dev)
{
	struct ahci_channel *ch = device_get_softc(dev);

	/* Disable port interrupts. */
	ATA_OUTL(ch->r_mem, AHCI_P_IE, 0);
	/* Reset command register. */
	ahci_stop(ch);
	ahci_stop_fr(ch);
	ATA_OUTL(ch->r_mem, AHCI_P_CMD, 0);
	/* Allow everything, including partial and slumber modes. */
	ATA_OUTL(ch->r_mem, AHCI_P_SCTL, 0);
	/* Request slumber mode transition and give some time to get there. */
	ATA_OUTL(ch->r_mem, AHCI_P_CMD, AHCI_P_CMD_SLUMBER);
	DELAY(100);
	/* Disable PHY. */
	ATA_OUTL(ch->r_mem, AHCI_P_SCTL, ATA_SC_DET_DISABLE);
	return (0);
}