#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct ccb_scsiio {TYPE_2__ ccb_h; } ;
struct TYPE_9__ {int /*<<< orphan*/  softs; int /*<<< orphan*/  status; TYPE_1__* cm_ccb; } ;
typedef  TYPE_3__ rcb_t ;
struct TYPE_7__ {int /*<<< orphan*/  csio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  DBG_IO (char*,...) ; 
 int /*<<< orphan*/  REQUEST_SUCCESS ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pqi_release_camq (TYPE_3__*) ; 
 int /*<<< orphan*/  pqi_unmap_request (TYPE_3__*) ; 
 int /*<<< orphan*/  smartpqi_fix_ld_inquiry (int /*<<< orphan*/ ,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

void
os_io_response_success(rcb_t *rcb)
{
	struct ccb_scsiio		*csio;

	DBG_IO("IN rcb = %p\n", rcb);

	if (rcb == NULL) 
		panic("rcb is null");

	csio = (struct ccb_scsiio *)&rcb->cm_ccb->csio;
	
	if (csio == NULL) 
		panic("csio is null");

	rcb->status = REQUEST_SUCCESS;
	csio->ccb_h.status = CAM_REQ_CMP;

	smartpqi_fix_ld_inquiry(rcb->softs, csio);
	pqi_release_camq(rcb);
	pqi_unmap_request(rcb);
	xpt_done((union ccb *)csio);

	DBG_IO("OUT\n");
}