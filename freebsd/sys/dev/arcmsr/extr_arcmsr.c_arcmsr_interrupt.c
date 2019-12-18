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
struct AdapterControlBlock {int adapter_type; int pci_unit; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  arcmsr_handle_hba_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_handle_hbb_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_handle_hbc_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_handle_hbd_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_handle_hbe_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void arcmsr_interrupt(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A:
		arcmsr_handle_hba_isr(acb);
		break;
	case ACB_ADAPTER_TYPE_B:
		arcmsr_handle_hbb_isr(acb);
		break;
	case ACB_ADAPTER_TYPE_C:
		arcmsr_handle_hbc_isr(acb);
		break;
	case ACB_ADAPTER_TYPE_D:
		arcmsr_handle_hbd_isr(acb);
		break;
	case ACB_ADAPTER_TYPE_E:
		arcmsr_handle_hbe_isr(acb);
		break;
	default:
		printf("arcmsr%d: interrupt service,"
		" unknown adapter type =%d\n", acb->pci_unit, acb->adapter_type);
		break;
	}
}