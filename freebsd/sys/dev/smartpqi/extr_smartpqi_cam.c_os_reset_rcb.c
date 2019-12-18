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
struct TYPE_3__ {int status; int encrypt_enable; int req_pending; scalar_t__ resp_qid; scalar_t__ ioaccel_handle; int /*<<< orphan*/ * cm_ccb; int /*<<< orphan*/ * sgt; scalar_t__ nseg; scalar_t__ bcount; int /*<<< orphan*/ * cm_data; scalar_t__ cm_flags; int /*<<< orphan*/ * softs; int /*<<< orphan*/ * cdbp; int /*<<< orphan*/ * dvp; int /*<<< orphan*/  tag; int /*<<< orphan*/ * req; int /*<<< orphan*/ * error_info; } ;
typedef  TYPE_1__ rcb_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_ELEM ; 

void os_reset_rcb( rcb_t *rcb )
{
	rcb->error_info = NULL;
	rcb->req = NULL;
	rcb->status = -1;
	rcb->tag = INVALID_ELEM;
	rcb->dvp = NULL;
	rcb->cdbp = NULL;
	rcb->softs = NULL;
	rcb->cm_flags = 0;
	rcb->cm_data = NULL;
	rcb->bcount = 0;	
	rcb->nseg = 0;
	rcb->sgt = NULL;
	rcb->cm_ccb = NULL;
	rcb->encrypt_enable = false;
	rcb->ioaccel_handle = 0;
	rcb->resp_qid = 0;
	rcb->req_pending = false;
}