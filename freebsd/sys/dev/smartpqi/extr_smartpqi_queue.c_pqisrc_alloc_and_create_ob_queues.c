#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {char* tag; int size; char* virt_addr; int dma_addr; int /*<<< orphan*/  align; } ;
struct TYPE_10__ {int num_op_obq; int num_elem_per_op_obq; int obq_elem_size; int share_opq_and_eventq; TYPE_2__* op_ob_q; TYPE_8__ op_obq_dma_mem; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
struct TYPE_11__ {int q_id; int intr_msg_num; int num_elem; int elem_size; int pi_dma_addr; int* pi_virt_addr; int created; } ;
typedef  TYPE_2__ ob_queue_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_BOUNDARY (int,int) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int /*<<< orphan*/  DBG_INFO (char*,int) ; 
 int /*<<< orphan*/  FILL_QUEUE_ARRAY_ADDR (TYPE_2__*,char*,int) ; 
 int PQI_ADDR_ALIGN_MASK_4 ; 
 int PQI_ADDR_ALIGN_MASK_64 ; 
 int PQI_MIN_OP_OB_QUEUE_ID ; 
 int /*<<< orphan*/  PQI_OPQ_ELEM_ARRAY_ALIGN ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int os_dma_mem_alloc (TYPE_1__*,TYPE_8__*) ; 
 int pqisrc_create_op_obq (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pqisrc_destroy_op_ob_queues (TYPE_1__*) ; 

int pqisrc_alloc_and_create_ob_queues(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t alloc_size = 0;
	char *virt_addr = NULL;
	dma_addr_t dma_addr = 0;
	uint32_t obq_size = 0;
	uint32_t ob_pi_dma_start_offset = 0;
	uint32_t ob_pi_virt_start_offset = 0;
	char *ob_pi_virt_start_addr = NULL;
	uint32_t obq_id = PQI_MIN_OP_OB_QUEUE_ID;
	ob_queue_t *op_ob_q = NULL;
 	uint32_t num_op_obq = softs->num_op_obq;
	int i = 0;

	DBG_FUNC("IN\n");

	/* 
	 * OB Q element array should be 64 byte aligned. 
	 * So the number of elements in OB Q should be multiple 
	 * of 4, so that OB Queue element size (16) * num elements 
	 * will be multiple of 64.
	 */
	
	ALIGN_BOUNDARY(softs->num_elem_per_op_obq, 4);
	obq_size = softs->num_elem_per_op_obq *  softs->obq_elem_size;
	alloc_size += num_op_obq * obq_size;
	/* PI indexes starts after Queue element array */ 
	ob_pi_dma_start_offset = alloc_size;
	ob_pi_virt_start_offset = alloc_size;
	alloc_size += num_op_obq * sizeof(uint32_t); /*For OBQ PI*/

	/* Allocate memory for OB queues */
	softs->op_obq_dma_mem.tag = "op_ob_queue";
	softs->op_obq_dma_mem.size = alloc_size;
	softs->op_obq_dma_mem.align = PQI_OPQ_ELEM_ARRAY_ALIGN;
	ret = os_dma_mem_alloc(softs, &softs->op_obq_dma_mem);
	if (ret) {
		DBG_ERR("Failed to Allocate Operational OBQ memory ret : %d\n",
						ret);
		goto err_out;
	}

	/* Set up the address */
	virt_addr = softs->op_obq_dma_mem.virt_addr;
	dma_addr = softs->op_obq_dma_mem.dma_addr;
	ob_pi_dma_start_offset += dma_addr;
	ob_pi_virt_start_addr = virt_addr + ob_pi_virt_start_offset;

	DBG_INFO("softs->num_op_obq %d\n",softs->num_op_obq);

	for (i = 0; i <  softs->num_op_obq; i++) {		
		op_ob_q = &softs->op_ob_q[i];
		ASSERT(!(dma_addr & PQI_ADDR_ALIGN_MASK_64));
		FILL_QUEUE_ARRAY_ADDR(op_ob_q,virt_addr,dma_addr);
		op_ob_q->q_id = obq_id++;
		if(softs->share_opq_and_eventq == true)
			op_ob_q->intr_msg_num = i; 
		else
			op_ob_q->intr_msg_num = i + 1; /* msg num zero for event */ 
		op_ob_q->num_elem = softs->num_elem_per_op_obq;
		op_ob_q->elem_size = softs->obq_elem_size;
		op_ob_q->pi_dma_addr = ob_pi_dma_start_offset +
					(i * sizeof(uint32_t));
		op_ob_q->pi_virt_addr = (uint32_t*)(ob_pi_virt_start_addr +
					(i * sizeof(uint32_t)));
		ASSERT(!(op_ob_q->pi_dma_addr & PQI_ADDR_ALIGN_MASK_4));
		
		ret = pqisrc_create_op_obq(softs,op_ob_q);
		if (ret) {
			DBG_ERR("Failed to Create OP OBQ %d\n",op_ob_q->q_id);
			goto err_out_create;
		}
		op_ob_q->created  = true;
		virt_addr += obq_size;
		dma_addr += obq_size;
	}
	
	DBG_FUNC("OUT\n");
	return ret;
	
err_out_create:
	pqisrc_destroy_op_ob_queues(softs);
err_out:
	DBG_FUNC("OUT failed %d\n", ret);
	return PQI_STATUS_FAILURE;
}