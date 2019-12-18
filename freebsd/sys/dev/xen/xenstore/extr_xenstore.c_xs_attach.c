#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct proc {int /*<<< orphan*/  p_pid; } ;
struct evtchn_alloc_unbound {scalar_t__ port; void* remote_dom; void* dom; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int /*<<< orphan*/ * ich_arg; int /*<<< orphan*/  ich_func; } ;
struct TYPE_4__ {int initialized; scalar_t__ evtchn; int /*<<< orphan*/  xs_late_init; TYPE_3__ xs_attachcb; int /*<<< orphan*/  xenwatch_pid; int /*<<< orphan*/  watch_events_lock; int /*<<< orphan*/  registered_watches_lock; int /*<<< orphan*/  request_mutex; int /*<<< orphan*/  xenwatch_mutex; int /*<<< orphan*/  reply_lock; int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  watch_events; int /*<<< orphan*/  reply_list; int /*<<< orphan*/  gpfn; int /*<<< orphan*/  xs_dev; } ;

/* Variables and functions */
 void* DOMID_SELF ; 
 int /*<<< orphan*/  EVTCHNOP_alloc_unbound ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_alloc_unbound*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PAT_WRITE_BACK ; 
 int /*<<< orphan*/  RFHIGHPID ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_establish (TYPE_3__*) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int kproc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct proc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_mapdev_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xen_get_xenstore_evtchn () ; 
 int /*<<< orphan*/  xen_get_xenstore_mfn () ; 
 scalar_t__ xen_store ; 
 int /*<<< orphan*/  xenwatch_thread ; 
 TYPE_1__ xs ; 
 int /*<<< orphan*/  xs_attach_deferred ; 
 int /*<<< orphan*/  xs_attach_late ; 
 int xs_init_comms () ; 
 int /*<<< orphan*/  xs_rcv_thread ; 

__attribute__((used)) static int
xs_attach(device_t dev)
{
	int error;

	/* Allow us to get device_t from softc and vice-versa. */
	xs.xs_dev = dev;
	device_set_softc(dev, &xs);

	/* Initialize the interface to xenstore. */
	struct proc *p;

	xs.initialized = false;
	xs.evtchn = xen_get_xenstore_evtchn();
	if (xs.evtchn == 0) {
		struct evtchn_alloc_unbound alloc_unbound;

		/* Allocate a local event channel for xenstore */
		alloc_unbound.dom = DOMID_SELF;
		alloc_unbound.remote_dom = DOMID_SELF;
		error = HYPERVISOR_event_channel_op(
		    EVTCHNOP_alloc_unbound, &alloc_unbound);
		if (error != 0)
			panic(
			   "unable to alloc event channel for Dom0: %d",
			    error);

		xs.evtchn = alloc_unbound.port;

		/* Allocate memory for the xs shared ring */
		xen_store = malloc(PAGE_SIZE, M_XENSTORE, M_WAITOK | M_ZERO);
		xs.gpfn = atop(pmap_kextract((vm_offset_t)xen_store));
	} else {
		xs.gpfn = xen_get_xenstore_mfn();
		xen_store = pmap_mapdev_attr(ptoa(xs.gpfn), PAGE_SIZE,
		    PAT_WRITE_BACK);
		xs.initialized = true;
	}

	TAILQ_INIT(&xs.reply_list);
	TAILQ_INIT(&xs.watch_events);

	mtx_init(&xs.ring_lock, "ring lock", NULL, MTX_DEF);
	mtx_init(&xs.reply_lock, "reply lock", NULL, MTX_DEF);
	sx_init(&xs.xenwatch_mutex, "xenwatch");
	sx_init(&xs.request_mutex, "xenstore request");
	mtx_init(&xs.registered_watches_lock, "watches", NULL, MTX_DEF);
	mtx_init(&xs.watch_events_lock, "watch events", NULL, MTX_DEF);

	/* Initialize the shared memory rings to talk to xenstored */
	error = xs_init_comms();
	if (error)
		return (error);

	error = kproc_create(xenwatch_thread, NULL, &p, RFHIGHPID,
	    0, "xenwatch");
	if (error)
		return (error);
	xs.xenwatch_pid = p->p_pid;

	error = kproc_create(xs_rcv_thread, NULL, NULL,
	    RFHIGHPID, 0, "xenstore_rcv");

	xs.xs_attachcb.ich_func = xs_attach_deferred;
	xs.xs_attachcb.ich_arg = NULL;
	if (xs.initialized) {
		config_intrhook_establish(&xs.xs_attachcb);
	} else {
		TASK_INIT(&xs.xs_late_init, 0, xs_attach_late, NULL);
	}

	return (error);
}