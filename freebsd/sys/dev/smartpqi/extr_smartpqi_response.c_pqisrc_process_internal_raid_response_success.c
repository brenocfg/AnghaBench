#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int req_pending; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ rcb_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  REQUEST_SUCCESS ; 

void pqisrc_process_internal_raid_response_success(pqisrc_softstate_t *softs,
					  rcb_t *rcb) 
{
	DBG_FUNC("IN");

	rcb->status = REQUEST_SUCCESS;
	rcb->req_pending = false;

	DBG_FUNC("OUT");
}