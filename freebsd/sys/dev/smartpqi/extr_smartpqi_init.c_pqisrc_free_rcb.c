#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  rcb_t ;
struct TYPE_5__ {int max_outstanding_io; int /*<<< orphan*/ * rcb; int /*<<< orphan*/ * sg_dma_desc; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  os_dma_mem_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_mem_free (TYPE_1__*,void*,size_t) ; 

void pqisrc_free_rcb(pqisrc_softstate_t *softs, int req_count)
{
	
	uint32_t num_req;
	size_t size;
	int i;

	DBG_FUNC("IN\n");
	num_req = softs->max_outstanding_io + 1;
	size = num_req * sizeof(rcb_t);
	for (i = 1; i < req_count; i++)
		os_dma_mem_free(softs, &softs->sg_dma_desc[i]);
	os_mem_free(softs, (void *)softs->rcb, size);
	softs->rcb = NULL;
	DBG_FUNC("OUT\n");
}