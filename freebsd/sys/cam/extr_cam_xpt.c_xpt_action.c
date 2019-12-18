#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_5__* path; int /*<<< orphan*/  status; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct TYPE_10__ {TYPE_3__* bus; } ;
struct TYPE_9__ {TYPE_2__* ops; } ;
struct TYPE_8__ {TYPE_4__* xport; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* action ) (union ccb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_REQ_INPROG ; 
 int /*<<< orphan*/  stub1 (union ccb*) ; 
 int /*<<< orphan*/  xpt_action_name (int /*<<< orphan*/ ) ; 

void
xpt_action(union ccb *start_ccb)
{

	CAM_DEBUG(start_ccb->ccb_h.path, CAM_DEBUG_TRACE,
	    ("xpt_action: func %#x %s\n", start_ccb->ccb_h.func_code,
		xpt_action_name(start_ccb->ccb_h.func_code)));

	start_ccb->ccb_h.status = CAM_REQ_INPROG;
	(*(start_ccb->ccb_h.path->bus->xport->ops->action))(start_ccb);
}