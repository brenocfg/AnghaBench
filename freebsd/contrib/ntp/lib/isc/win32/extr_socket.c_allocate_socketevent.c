#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_taskaction_t ;
struct TYPE_10__ {int /*<<< orphan*/ * base; } ;
struct TYPE_11__ {int /*<<< orphan*/  ev_destroy; int /*<<< orphan*/  destroy; scalar_t__ attributes; scalar_t__ offset; scalar_t__ n; TYPE_2__ region; int /*<<< orphan*/  bufferlist; int /*<<< orphan*/  result; } ;
typedef  TYPE_3__ isc_socketevent_t ;
struct TYPE_12__ {TYPE_1__* manager; } ;
typedef  TYPE_4__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_eventtype_t ;
struct TYPE_9__ {int /*<<< orphan*/  mctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_IOERROR ; 
 int /*<<< orphan*/  destroy_socketevent ; 
 int /*<<< orphan*/  ev_link ; 
 scalar_t__ isc_event_allocate (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static isc_socketevent_t *
allocate_socketevent(isc_socket_t *sock, isc_eventtype_t eventtype,
		     isc_taskaction_t action, const void *arg)
{
	isc_socketevent_t *ev;

	ev = (isc_socketevent_t *)isc_event_allocate(sock->manager->mctx,
						     sock, eventtype,
						     action, arg,
						     sizeof(*ev));
	if (ev == NULL)
		return (NULL);

	ev->result = ISC_R_IOERROR; // XXXMLG temporary change to detect failure to set
	ISC_LINK_INIT(ev, ev_link);
	ISC_LIST_INIT(ev->bufferlist);
	ev->region.base = NULL;
	ev->n = 0;
	ev->offset = 0;
	ev->attributes = 0;
	ev->destroy = ev->ev_destroy;
	ev->ev_destroy = destroy_socketevent;

	return (ev);
}