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
struct mvs_channel {int /*<<< orphan*/  r_mem; int /*<<< orphan*/  curr_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDMA_IEC ; 
 int /*<<< orphan*/  EDMA_IEM ; 
 int EDMA_IE_TRANSIENT ; 
 int /*<<< orphan*/  MVS_EDMA_OFF ; 
 int /*<<< orphan*/  MVS_EDMA_UNKNOWN ; 
 int /*<<< orphan*/  SATA_FISC ; 
 int SATA_FISC_FISWAIT4HOSTRDYEN_B1 ; 
 int /*<<< orphan*/  SATA_FISIC ; 
 int /*<<< orphan*/  SATA_FISIM ; 
 int /*<<< orphan*/  SATA_SE ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_set_edma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvs_ch_init(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	uint32_t reg;

	/* Disable port interrupts */
	ATA_OUTL(ch->r_mem, EDMA_IEM, 0);
	/* Stop EDMA */
	ch->curr_mode = MVS_EDMA_UNKNOWN;
	mvs_set_edma_mode(dev, MVS_EDMA_OFF);
	/* Clear and configure FIS interrupts. */
	ATA_OUTL(ch->r_mem, SATA_FISIC, 0);
	reg = ATA_INL(ch->r_mem, SATA_FISC);
	reg |= SATA_FISC_FISWAIT4HOSTRDYEN_B1;
	ATA_OUTL(ch->r_mem, SATA_FISC, reg);
	reg = ATA_INL(ch->r_mem, SATA_FISIM);
	reg |= SATA_FISC_FISWAIT4HOSTRDYEN_B1;
	ATA_OUTL(ch->r_mem, SATA_FISC, reg);
	/* Clear SATA error register. */
	ATA_OUTL(ch->r_mem, SATA_SE, 0xffffffff);
	/* Clear any outstanding error interrupts. */
	ATA_OUTL(ch->r_mem, EDMA_IEC, 0);
	/* Unmask all error interrupts */
	ATA_OUTL(ch->r_mem, EDMA_IEM, ~EDMA_IE_TRANSIENT);
	return (0);
}