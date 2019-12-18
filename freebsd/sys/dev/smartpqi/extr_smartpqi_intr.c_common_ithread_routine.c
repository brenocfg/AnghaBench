#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_2__ {int oq_id; int /*<<< orphan*/  pqi_dev; } ;
typedef  TYPE_1__ pqi_intr_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/ * device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_process_response_queue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void common_ithread_routine(void *arg)
{
	pqi_intr_ctx_t *intr_ctx = (pqi_intr_ctx_t *)arg;
	pqisrc_softstate_t *softs = device_get_softc(intr_ctx->pqi_dev);
	int oq_id  = intr_ctx->oq_id;

	DBG_FUNC("IN\n");
	
	pqisrc_process_response_queue(softs, oq_id);

	DBG_FUNC("OUT\n");
}