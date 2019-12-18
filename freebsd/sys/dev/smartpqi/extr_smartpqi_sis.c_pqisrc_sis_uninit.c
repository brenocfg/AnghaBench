#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  err_buf_dma_mem; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  os_dma_mem_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_resource_free (TYPE_1__*) ; 
 int /*<<< orphan*/  pqi_reset (TYPE_1__*) ; 

void pqisrc_sis_uninit(pqisrc_softstate_t *softs)
{
	DBG_FUNC("IN\n");

	os_dma_mem_free(softs, &softs->err_buf_dma_mem);
	os_resource_free(softs);
	pqi_reset(softs);

	DBG_FUNC("OUT\n");
}