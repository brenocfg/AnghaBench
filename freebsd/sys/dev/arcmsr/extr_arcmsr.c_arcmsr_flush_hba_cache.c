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
struct AdapterControlBlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_INBOUND_MESG0_FLUSH_CACHE ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 scalar_t__ arcmsr_hba_wait_msgint_ready (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  inbound_msgaddr0 ; 

__attribute__((used)) static void arcmsr_flush_hba_cache(struct AdapterControlBlock *acb)
{
	int retry_count = 30;/* enlarge wait flush adapter cache time: 10 minute */

	CHIP_REG_WRITE32(HBA_MessageUnit, 0, inbound_msgaddr0, ARCMSR_INBOUND_MESG0_FLUSH_CACHE);
	do {
		if(arcmsr_hba_wait_msgint_ready(acb)) {
			break;
		} else {
			retry_count--;
		}
	}while(retry_count != 0);
}