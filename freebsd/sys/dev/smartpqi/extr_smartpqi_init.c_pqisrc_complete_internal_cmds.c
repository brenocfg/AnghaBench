#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int req_pending; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ rcb_t ;
struct TYPE_6__ {int max_outstanding_io; TYPE_1__* rcb; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_FAILED ; 
 scalar_t__ is_internal_req (TYPE_1__*) ; 

void pqisrc_complete_internal_cmds(pqisrc_softstate_t *softs)
{
	int tag = 0;
	rcb_t *rcb;
	
	for (tag = 1; tag <= softs->max_outstanding_io; tag++) {
		rcb = &softs->rcb[tag];
		if(rcb->req_pending && is_internal_req(rcb)) {
			rcb->status = REQUEST_FAILED;
			rcb->req_pending = false;
		}
	}
}