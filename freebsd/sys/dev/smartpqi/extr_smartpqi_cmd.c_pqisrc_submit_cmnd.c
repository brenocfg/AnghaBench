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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_4__ {int iu_length; } ;
typedef  TYPE_1__ iu_header_t ;
struct TYPE_5__ {int pi_local; int num_elem; int* ci_virt_addr; int elem_size; char* array_virt_addr; int /*<<< orphan*/  lock; int /*<<< orphan*/  pi_register_offset; int /*<<< orphan*/  pi_register_abs; } ;
typedef  TYPE_2__ ib_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INFO (char*,...) ; 
 int /*<<< orphan*/  DBG_WARN (char*) ; 
 int /*<<< orphan*/  PCI_MEM_PUT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PQI_LOCK (int /*<<< orphan*/ *) ; 
 int PQI_STATUS_QFULL ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  PQI_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 

int pqisrc_submit_cmnd(pqisrc_softstate_t *softs, 
				ib_queue_t *ib_q, void *req)
{
	char *slot = NULL;
	uint32_t offset;
	iu_header_t *hdr = (iu_header_t *)req;
	uint32_t iu_len = hdr->iu_length + 4 ; /* header size */
	int i = 0;
	DBG_FUNC("IN\n");

	PQI_LOCK(&ib_q->lock);
	
	/* Check queue full */
	if ((ib_q->pi_local + 1) % ib_q->num_elem == *(ib_q->ci_virt_addr)) {
		DBG_WARN("OUT Q full\n");
	PQI_UNLOCK(&ib_q->lock);	
		return PQI_STATUS_QFULL;
	}

	/* Get the slot */
	offset = ib_q->pi_local * ib_q->elem_size;
	slot = ib_q->array_virt_addr + offset;

	/* Copy the IU */
	memcpy(slot, req, iu_len);
	DBG_INFO("IU : \n");
	for(i = 0; i< iu_len; i++)
		DBG_INFO(" IU [ %d ] : %x\n", i, *((unsigned char *)(slot + i)));

	/* Update the local PI */
	ib_q->pi_local = (ib_q->pi_local + 1) % ib_q->num_elem;
	DBG_INFO("ib_q->pi_local : %x IU size : %d\n",
			 ib_q->pi_local, hdr->iu_length);
	DBG_INFO("*ib_q->ci_virt_addr: %x\n",
				*(ib_q->ci_virt_addr));

	/* Inform the fw about the new IU */
	PCI_MEM_PUT32(softs, ib_q->pi_register_abs, ib_q->pi_register_offset, ib_q->pi_local);
	PQI_UNLOCK(&ib_q->lock);	
	DBG_FUNC("OUT\n");
	return PQI_STATUS_SUCCESS;
}