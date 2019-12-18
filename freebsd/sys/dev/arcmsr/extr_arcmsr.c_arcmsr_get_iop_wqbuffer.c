#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct QBUFFER {int dummy; } ;
struct HBE_MessageUnit {int /*<<< orphan*/  message_wbuffer; } ;
struct HBD_MessageUnit0 {TYPE_2__* phbdmu; } ;
struct HBC_MessageUnit {int /*<<< orphan*/  message_wbuffer; } ;
struct HBB_MessageUnit {TYPE_1__* hbb_rwbuffer; } ;
struct HBA_MessageUnit {int /*<<< orphan*/  message_wbuffer; } ;
struct AdapterControlBlock {int adapter_type; scalar_t__ pmu; } ;
struct TYPE_4__ {int /*<<< orphan*/  message_wbuffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  message_wbuffer; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 

__attribute__((used)) static struct QBUFFER *arcmsr_get_iop_wqbuffer( struct AdapterControlBlock *acb)
{
	struct QBUFFER *qbuffer = NULL;

	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
			struct HBA_MessageUnit *phbamu = (struct HBA_MessageUnit *)acb->pmu;

			qbuffer = (struct QBUFFER *)&phbamu->message_wbuffer;
		}
		break;
	case ACB_ADAPTER_TYPE_B: {
			struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;

			qbuffer = (struct QBUFFER *)&phbbmu->hbb_rwbuffer->message_wbuffer;
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
			struct HBC_MessageUnit *phbcmu = (struct HBC_MessageUnit *)acb->pmu;

			qbuffer = (struct QBUFFER *)&phbcmu->message_wbuffer;
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
			struct HBD_MessageUnit0 *phbdmu = (struct HBD_MessageUnit0 *)acb->pmu;

			qbuffer = (struct QBUFFER *)&phbdmu->phbdmu->message_wbuffer;
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
			struct HBE_MessageUnit *phbcmu = (struct HBE_MessageUnit *)acb->pmu;
	
			qbuffer = (struct QBUFFER *)&phbcmu->message_wbuffer;
		}
		break;
	}
	return(qbuffer);
}