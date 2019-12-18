#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct TYPE_10__ {union ccb* ccb; } ;
typedef  TYPE_2__ pduq_t ;
struct TYPE_11__ {int /*<<< orphan*/  isc; } ;
typedef  TYPE_3__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  XPT_DONE (TYPE_3__*,union ccb*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  pdu_free (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
iscsi_reject(isc_session_t *sp, pduq_t *opq, pduq_t *pq)
{
     union ccb 		*ccb = opq->ccb;
     //reject_t		*reject = &pq->pdu.ipdu.reject;

     debug_called(8);
     //XXX: check RFC 10.17.1 (page 176)
     ccb->ccb_h.status = CAM_REQ_ABORTED;
     XPT_DONE(sp, ccb);
 
     pdu_free(sp->isc, opq);
}