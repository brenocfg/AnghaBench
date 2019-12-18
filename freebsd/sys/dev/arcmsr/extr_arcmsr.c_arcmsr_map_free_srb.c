#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct CommandControlBlock {unsigned long cdb_phyaddr_low; int cdb_phyaddr_high; int smid; struct AdapterControlBlock* acb; int /*<<< orphan*/  dm_segs_dmamap; } ;
struct TYPE_4__ {unsigned long phyaddr; } ;
struct AdapterControlBlock {int pci_unit; scalar_t__ adapter_type; unsigned long vir2phy_offset; scalar_t__ pCompletionQ; struct CommandControlBlock** psrb_pool; struct CommandControlBlock** srbworkingQ; int /*<<< orphan*/  acb_flags; int /*<<< orphan*/  dm_segs_dmat; scalar_t__ uncacheptr; TYPE_1__ srb_phyaddr; } ;
typedef  scalar_t__ pCompletion_Q ;
struct TYPE_5__ {scalar_t__ ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;

/* Variables and functions */
 scalar_t__ ACB_ADAPTER_TYPE_C ; 
 scalar_t__ ACB_ADAPTER_TYPE_D ; 
 scalar_t__ ACB_ADAPTER_TYPE_E ; 
 int /*<<< orphan*/  ACB_F_MAPFREESRB_FAILD ; 
 int ARCMSR_MAX_FREESRB_NUM ; 
 unsigned long SRB_SIZE ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void arcmsr_map_free_srb(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct AdapterControlBlock *acb = arg;
	struct CommandControlBlock *srb_tmp;
	u_int32_t i;
	unsigned long srb_phyaddr = (unsigned long)segs->ds_addr;

	acb->srb_phyaddr.phyaddr = srb_phyaddr; 
	srb_tmp = (struct CommandControlBlock *)acb->uncacheptr;
	for(i=0; i < ARCMSR_MAX_FREESRB_NUM; i++) {
		if(bus_dmamap_create(acb->dm_segs_dmat,
			 /*flags*/0, &srb_tmp->dm_segs_dmamap) != 0) {
			acb->acb_flags |= ACB_F_MAPFREESRB_FAILD;
			printf("arcmsr%d:"
			" srb dmamap bus_dmamap_create error\n", acb->pci_unit);
			return;
		}
		if((acb->adapter_type == ACB_ADAPTER_TYPE_C) || (acb->adapter_type == ACB_ADAPTER_TYPE_D)
			 || (acb->adapter_type == ACB_ADAPTER_TYPE_E))
		{
			srb_tmp->cdb_phyaddr_low = srb_phyaddr;
			srb_tmp->cdb_phyaddr_high = (u_int32_t)((srb_phyaddr >> 16) >> 16);
		}
		else
			srb_tmp->cdb_phyaddr_low = srb_phyaddr >> 5;
		srb_tmp->acb = acb;
		srb_tmp->smid = i << 16;
		acb->srbworkingQ[i] = acb->psrb_pool[i] = srb_tmp;
		srb_phyaddr = srb_phyaddr + SRB_SIZE;
		srb_tmp = (struct CommandControlBlock *)((unsigned long)srb_tmp + SRB_SIZE);
	}
	if (acb->adapter_type == ACB_ADAPTER_TYPE_E)
		acb->pCompletionQ = (pCompletion_Q)srb_tmp;
	acb->vir2phy_offset = (unsigned long)srb_tmp - (unsigned long)srb_phyaddr;
}