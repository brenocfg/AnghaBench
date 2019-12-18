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
struct AdapterControlBlock {scalar_t__ pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_MESSAGE_FLUSH_CACHE ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ arcmsr_hbb_wait_msgint_ready (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_flush_hbb_cache(struct AdapterControlBlock *acb)
{
	int retry_count = 30;/* enlarge wait flush adapter cache time: 10 minute */
	struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;

	WRITE_CHIP_REG32(0, phbbmu->drv2iop_doorbell, ARCMSR_MESSAGE_FLUSH_CACHE);
	do {
		if(arcmsr_hbb_wait_msgint_ready(acb)) {
			break;
		} else {
			retry_count--;
		}
	}while(retry_count != 0);
}