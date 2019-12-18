#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* num_elem; } ;
struct TYPE_5__ {void* num_elem; } ;
struct TYPE_7__ {TYPE_2__ admin_ob_queue; TYPE_1__ admin_ib_queue; } ;
typedef  TYPE_3__ pqisrc_softstate_t ;

/* Variables and functions */
 void* MIN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQISRC_MAX_ADMIN_IB_QUEUE_ELEM_NUM ; 
 int /*<<< orphan*/  PQISRC_MAX_ADMIN_OB_QUEUE_ELEM_NUM ; 

void pqisrc_decide_admin_queue_config(pqisrc_softstate_t *softs)
{
	/* Determine  num elements in Admin IBQ  */
	softs->admin_ib_queue.num_elem = MIN(softs->admin_ib_queue.num_elem,
					PQISRC_MAX_ADMIN_IB_QUEUE_ELEM_NUM);
					
	/* Determine  num elements in Admin OBQ  */
	softs->admin_ob_queue.num_elem = MIN(softs->admin_ob_queue.num_elem,
					PQISRC_MAX_ADMIN_OB_QUEUE_ELEM_NUM);
}