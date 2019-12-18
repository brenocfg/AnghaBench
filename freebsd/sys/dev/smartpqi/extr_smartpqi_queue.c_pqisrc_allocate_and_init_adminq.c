#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int num_elem; int elem_size; char* array_virt_addr; int array_dma_addr; int* pi_virt_addr; int pi_dma_addr; scalar_t__ ci_local; scalar_t__ q_id; } ;
struct TYPE_7__ {int num_elem; int elem_size; char* array_virt_addr; int array_dma_addr; int* ci_virt_addr; int ci_dma_addr; scalar_t__ pi_local; scalar_t__ q_id; } ;
struct TYPE_10__ {char* tag; int size; char* virt_addr; void* dma_addr; int /*<<< orphan*/  align; } ;
struct TYPE_9__ {TYPE_2__ admin_ob_queue; TYPE_1__ admin_ib_queue; TYPE_6__ admin_queue_dma_mem; } ;
typedef  TYPE_3__ pqisrc_softstate_t ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INIT (char*,void*,void*) ; 
 int PQI_ADDR_ALIGN_MASK_64 ; 
 int /*<<< orphan*/  PQI_ADMINQ_ELEM_ARRAY_ALIGN ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int os_dma_mem_alloc (TYPE_3__*,TYPE_6__*) ; 

int pqisrc_allocate_and_init_adminq(pqisrc_softstate_t *softs)
{
	uint32_t ib_array_size = 0;
	uint32_t ob_array_size = 0;
	uint32_t alloc_size = 0;
	char *virt_addr = NULL;
	dma_addr_t dma_addr = 0;
	int ret = PQI_STATUS_SUCCESS;

	ib_array_size = (softs->admin_ib_queue.num_elem *
			softs->admin_ib_queue.elem_size);
	
	ob_array_size = (softs->admin_ob_queue.num_elem *
			softs->admin_ob_queue.elem_size);

	alloc_size = ib_array_size + ob_array_size +
			2 * sizeof(uint32_t) + PQI_ADDR_ALIGN_MASK_64 + 1; /* for IB CI and OB PI */
	/* Allocate memory for Admin Q */
	softs->admin_queue_dma_mem.tag = "admin_queue";
	softs->admin_queue_dma_mem.size = alloc_size;
	softs->admin_queue_dma_mem.align = PQI_ADMINQ_ELEM_ARRAY_ALIGN;
	ret = os_dma_mem_alloc(softs, &softs->admin_queue_dma_mem);
	if (ret) {
		DBG_ERR("Failed to Allocate Admin Q ret : %d\n", ret);
		goto err_out;
	}

	/* Setup the address */
	virt_addr = softs->admin_queue_dma_mem.virt_addr;
	dma_addr = softs->admin_queue_dma_mem.dma_addr;

	/* IB */
	softs->admin_ib_queue.q_id = 0;
	softs->admin_ib_queue.array_virt_addr = virt_addr;
	softs->admin_ib_queue.array_dma_addr = dma_addr;
	softs->admin_ib_queue.pi_local = 0;
	/* OB */
	softs->admin_ob_queue.q_id = 0;
	softs->admin_ob_queue.array_virt_addr = virt_addr + ib_array_size;
	softs->admin_ob_queue.array_dma_addr = dma_addr + ib_array_size;
	softs->admin_ob_queue.ci_local = 0;
	
	/* IB CI */
	softs->admin_ib_queue.ci_virt_addr =
		(uint32_t*)((uint8_t*)softs->admin_ob_queue.array_virt_addr 
				+ ob_array_size);
	softs->admin_ib_queue.ci_dma_addr =
		(dma_addr_t)((uint8_t*)softs->admin_ob_queue.array_dma_addr + 
				ob_array_size);

	/* OB PI */
	softs->admin_ob_queue.pi_virt_addr =
		(uint32_t*)((uint8_t*)(softs->admin_ib_queue.ci_virt_addr) +  
		PQI_ADDR_ALIGN_MASK_64 + 1);
	softs->admin_ob_queue.pi_dma_addr =
		(dma_addr_t)((uint8_t*)(softs->admin_ib_queue.ci_dma_addr) +  
		PQI_ADDR_ALIGN_MASK_64 + 1);

	DBG_INIT("softs->admin_ib_queue.ci_dma_addr : %p,softs->admin_ob_queue.pi_dma_addr :%p\n",
				(void*)softs->admin_ib_queue.ci_dma_addr, (void*)softs->admin_ob_queue.pi_dma_addr );

	/* Verify alignment */
	ASSERT(!(softs->admin_ib_queue.array_dma_addr &
				PQI_ADDR_ALIGN_MASK_64));
	ASSERT(!(softs->admin_ib_queue.ci_dma_addr &
				PQI_ADDR_ALIGN_MASK_64));
	ASSERT(!(softs->admin_ob_queue.array_dma_addr &
				PQI_ADDR_ALIGN_MASK_64));
	ASSERT(!(softs->admin_ob_queue.pi_dma_addr &
				PQI_ADDR_ALIGN_MASK_64));

	DBG_FUNC("OUT\n");
	return ret;

err_out:
	DBG_FUNC("failed OUT\n");
	return PQI_STATUS_FAILURE;
}