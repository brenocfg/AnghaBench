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
struct HBB_MessageUnit {int /*<<< orphan*/  drv2iop_doorbell; } ;
struct AdapterControlBlock {int pci_unit; scalar_t__ pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_MESSAGE_ABORT_CMD ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_hbb_wait_msgint_ready (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void arcmsr_abort_hbb_allcmd(struct AdapterControlBlock *acb)
{
	struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
	WRITE_CHIP_REG32(0, phbbmu->drv2iop_doorbell, ARCMSR_MESSAGE_ABORT_CMD);
	if(!arcmsr_hbb_wait_msgint_ready(acb)) {
		printf("arcmsr%d: wait 'abort all outstanding command' timeout \n", acb->pci_unit);
	}
}