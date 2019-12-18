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
struct fsl_sata_channel {scalar_t__ numrslots; int pm_level; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FSL_SATA_PCC_LPB_EN ; 
 int /*<<< orphan*/  FSL_SATA_P_PCC ; 
 int FSL_SATA_P_PCC_PARTIAL ; 
 int FSL_SATA_P_PCC_SLUMBER ; 

__attribute__((used)) static void
fsl_sata_pm(void *arg)
{
	struct fsl_sata_channel *ch = (struct fsl_sata_channel *)arg;
	uint32_t work;

	if (ch->numrslots != 0)
		return;
	work = ATA_INL(ch->r_mem, FSL_SATA_P_PCC) & ~FSL_SATA_PCC_LPB_EN;
	if (ch->pm_level == 4)
		work |= FSL_SATA_P_PCC_PARTIAL;
	else
		work |= FSL_SATA_P_PCC_SLUMBER;
	ATA_OUTL(ch->r_mem, FSL_SATA_P_PCC, work);
}