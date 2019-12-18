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
struct CommandControlBlock {int dummy; } ;
struct AdapterControlBlock {int adapter_type; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  arcmsr_polling_hba_srbdone (struct AdapterControlBlock*,struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_polling_hbb_srbdone (struct AdapterControlBlock*,struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_polling_hbc_srbdone (struct AdapterControlBlock*,struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_polling_hbd_srbdone (struct AdapterControlBlock*,struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_polling_hbe_srbdone (struct AdapterControlBlock*,struct CommandControlBlock*) ; 

__attribute__((used)) static void arcmsr_polling_srbdone(struct AdapterControlBlock *acb, struct CommandControlBlock *poll_srb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
			arcmsr_polling_hba_srbdone(acb, poll_srb);
		}
		break;
	case ACB_ADAPTER_TYPE_B: {
			arcmsr_polling_hbb_srbdone(acb, poll_srb);
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
			arcmsr_polling_hbc_srbdone(acb, poll_srb);
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
			arcmsr_polling_hbd_srbdone(acb, poll_srb);
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
			arcmsr_polling_hbe_srbdone(acb, poll_srb);
		}
		break;
	}
}