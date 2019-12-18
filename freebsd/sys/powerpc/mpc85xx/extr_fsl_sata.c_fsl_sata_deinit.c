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
struct fsl_sata_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ATA_SC_DET_DISABLE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FSL_SATA_P_HCTRL ; 
 int FSL_SATA_P_HCTRL_HC_ON ; 
 int FSL_SATA_P_HCTRL_INT_MASK ; 
 int /*<<< orphan*/  FSL_SATA_P_SCTL ; 
 struct fsl_sata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_stop (struct fsl_sata_channel*) ; 

__attribute__((used)) static int
fsl_sata_deinit(device_t dev)
{
	struct fsl_sata_channel *ch = device_get_softc(dev);
	uint32_t r;

	/* Disable port interrupts. */
	r = ATA_INL(ch->r_mem, FSL_SATA_P_HCTRL);
	ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL, r & ~FSL_SATA_P_HCTRL_INT_MASK);
	/* Reset command register. */
	fsl_sata_stop(ch);
	/* Allow everything, including partial and slumber modes. */
	ATA_OUTL(ch->r_mem, FSL_SATA_P_SCTL, 0);
	DELAY(100);
	/* Disable PHY. */
	ATA_OUTL(ch->r_mem, FSL_SATA_P_SCTL, ATA_SC_DET_DISABLE);
	r = ATA_INL(ch->r_mem, FSL_SATA_P_HCTRL);
	/* Turn off the controller. */
	ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL, r & ~FSL_SATA_P_HCTRL_HC_ON);
	return (0);
}