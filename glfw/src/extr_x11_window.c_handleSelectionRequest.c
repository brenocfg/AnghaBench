#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  requestor; int /*<<< orphan*/  time; int /*<<< orphan*/  target; int /*<<< orphan*/  selection; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ XSelectionRequestEvent ;
struct TYPE_9__ {int /*<<< orphan*/  time; int /*<<< orphan*/  target; int /*<<< orphan*/  selection; int /*<<< orphan*/  requestor; int /*<<< orphan*/  display; int /*<<< orphan*/  property; } ;
struct TYPE_12__ {TYPE_1__ xselection; int /*<<< orphan*/  member_0; TYPE_3__ xselectionrequest; } ;
typedef  TYPE_4__ XEvent ;
struct TYPE_10__ {int /*<<< orphan*/  display; } ;
struct TYPE_13__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  SelectionNotify ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  writeTargetToProperty (TYPE_3__ const*) ; 

__attribute__((used)) static void handleSelectionRequest(XEvent* event)
{
    const XSelectionRequestEvent* request = &event->xselectionrequest;

    XEvent reply = { SelectionNotify };
    reply.xselection.property = writeTargetToProperty(request);
    reply.xselection.display = request->display;
    reply.xselection.requestor = request->requestor;
    reply.xselection.selection = request->selection;
    reply.xselection.target = request->target;
    reply.xselection.time = request->time;

    XSendEvent(_glfw.x11.display, request->requestor, False, 0, &reply);
}