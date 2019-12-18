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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct CommandControlBlock {scalar_t__ srb_state; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {int adapter_type; int vir2phy_offset; int pci_unit; int srboutstandingcount; struct CommandControlBlock** psrb_pool; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 scalar_t__ ARCMSR_SRB_START ; 
 scalar_t__ ARCMSR_SRB_TIMEOUT ; 
 int /*<<< orphan*/  arcmsr_free_srb (struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_report_srb_state (struct AdapterControlBlock*,struct CommandControlBlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,struct CommandControlBlock*,...) ; 

__attribute__((used)) static void arcmsr_drain_donequeue(struct AdapterControlBlock *acb, u_int32_t flag_srb, u_int16_t error)
{
	struct CommandControlBlock *srb;

	/* check if command done with no error*/
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A:
	case ACB_ADAPTER_TYPE_B:
		srb = (struct CommandControlBlock *)(acb->vir2phy_offset+(flag_srb << 5));/*frame must be 32 bytes aligned*/
		break;
	case ACB_ADAPTER_TYPE_C:
	case ACB_ADAPTER_TYPE_D:
		srb = (struct CommandControlBlock *)(acb->vir2phy_offset+(flag_srb & 0xFFFFFFE0)); /*frame must be 32 bytes aligned*/
		break;
	case ACB_ADAPTER_TYPE_E:
		srb = acb->psrb_pool[flag_srb];
		break;
	default:
		srb = (struct CommandControlBlock *)(acb->vir2phy_offset+(flag_srb << 5));/*frame must be 32 bytes aligned*/
		break;
	}
	if((srb->acb != acb) || (srb->srb_state != ARCMSR_SRB_START)) {
		if(srb->srb_state == ARCMSR_SRB_TIMEOUT) {
			arcmsr_free_srb(srb);
			printf("arcmsr%d: srb='%p' return srb has been timeouted\n", acb->pci_unit, srb);
			return;
		}
		printf("arcmsr%d: return srb has been completed\n"
			"srb='%p' srb_state=0x%x outstanding srb count=%d \n",
			acb->pci_unit, srb, srb->srb_state, acb->srboutstandingcount);
		return;
	}
	arcmsr_report_srb_state(acb, srb, error);
}