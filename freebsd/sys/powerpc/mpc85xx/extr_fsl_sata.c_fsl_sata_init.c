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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int work_bus; } ;
struct fsl_sata_channel {int /*<<< orphan*/  r_mem; TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FSL_SATA_CL_OFFSET ; 
 int FSL_SATA_PCC_LPB_EN ; 
 int /*<<< orphan*/  FSL_SATA_P_CHBA ; 
 int /*<<< orphan*/  FSL_SATA_P_HCTRL ; 
 int FSL_SATA_P_HCTRL_ENT ; 
 int FSL_SATA_P_HCTRL_HC_FORCE_OFF ; 
 int FSL_SATA_P_HCTRL_HC_ON ; 
 int FSL_SATA_P_HCTRL_INT_MASK ; 
 int FSL_SATA_P_HCTRL_PM ; 
 int /*<<< orphan*/  FSL_SATA_P_HSTS ; 
 int /*<<< orphan*/  FSL_SATA_P_HSTS_HS_ON ; 
 int /*<<< orphan*/  FSL_SATA_P_ICC ; 
 int FSL_SATA_P_ICC_ITC_S ; 
 int /*<<< orphan*/  FSL_SATA_P_PCC ; 
 struct fsl_sata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_start (struct fsl_sata_channel*) ; 
 int /*<<< orphan*/  fsl_sata_wait_register (struct fsl_sata_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fsl_sata_init(device_t dev)
{
	struct fsl_sata_channel *ch = device_get_softc(dev);
	uint64_t work;
	uint32_t r;

	/* Disable port interrupts */
	r = ATA_INL(ch->r_mem, FSL_SATA_P_HCTRL);
	r &= ~FSL_SATA_P_HCTRL_HC_ON;
	r |= FSL_SATA_P_HCTRL_HC_FORCE_OFF;
	ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL, r & ~FSL_SATA_P_HCTRL_INT_MASK);
	fsl_sata_wait_register(ch, FSL_SATA_P_HSTS,
	    FSL_SATA_P_HSTS_HS_ON, 0, 1000);
	/* Setup work areas */
	work = ch->dma.work_bus + FSL_SATA_CL_OFFSET;
	ATA_OUTL(ch->r_mem, FSL_SATA_P_CHBA, work);
	r &= ~FSL_SATA_P_HCTRL_ENT;
	r &= ~FSL_SATA_P_HCTRL_PM;
	ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL, r);
	r = ATA_INL(ch->r_mem, FSL_SATA_P_PCC);
	ATA_OUTL(ch->r_mem, FSL_SATA_P_PCC, r & ~FSL_SATA_PCC_LPB_EN);
	ATA_OUTL(ch->r_mem, FSL_SATA_P_ICC, (1 << FSL_SATA_P_ICC_ITC_S));
	fsl_sata_start(ch);
	return (0);
}