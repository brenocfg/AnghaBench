#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctl_softc {int /*<<< orphan*/  ctl_lock; struct ctl_port** ctl_ports; int /*<<< orphan*/  port_list; int /*<<< orphan*/  ctl_port_mask; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  port_max; int /*<<< orphan*/  port_min; } ;
struct TYPE_3__ {int item; } ;
struct ctl_port {int targ_port; int max_initiators; TYPE_2__* frontend; int /*<<< orphan*/  port_lock; TYPE_1__ stats; int /*<<< orphan*/ * options; void* ctl_pool_ref; int /*<<< orphan*/ * wwpn_iid; scalar_t__ num_requested_ctl_io; int /*<<< orphan*/  port_name; struct ctl_softc* ctl_softc; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int CTL_MAX_INIT_PER_PORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct ctl_port* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct ctl_port*,struct ctl_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ctl_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ctl_port*,int /*<<< orphan*/ ) ; 
 struct ctl_port* STAILQ_NEXT (struct ctl_port*,int /*<<< orphan*/ ) ; 
 struct ctl_softc* control_softc ; 
 int /*<<< orphan*/  ctl_clear_mask (int /*<<< orphan*/ ,int) ; 
 int ctl_ffz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctl_pool_create (struct ctl_softc*,int /*<<< orphan*/ ,scalar_t__,void**) ; 
 scalar_t__ ctl_set_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fe_links ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 

int
ctl_port_register(struct ctl_port *port)
{
	struct ctl_softc *softc = control_softc;
	struct ctl_port *tport, *nport;
	void *pool;
	int port_num;
	int retval;

	KASSERT(softc != NULL, ("CTL is not initialized"));
	port->ctl_softc = softc;

	mtx_lock(&softc->ctl_lock);
	if (port->targ_port >= 0)
		port_num = port->targ_port;
	else
		port_num = ctl_ffz(softc->ctl_port_mask,
		    softc->port_min, softc->port_max);
	if ((port_num < 0) ||
	    (ctl_set_mask(softc->ctl_port_mask, port_num) < 0)) {
		mtx_unlock(&softc->ctl_lock);
		return (1);
	}
	softc->num_ports++;
	mtx_unlock(&softc->ctl_lock);

	/*
	 * Initialize the initiator and portname mappings
	 */
	port->max_initiators = CTL_MAX_INIT_PER_PORT;
	port->wwpn_iid = malloc(sizeof(*port->wwpn_iid) * port->max_initiators,
	    M_CTL, M_NOWAIT | M_ZERO);
	if (port->wwpn_iid == NULL) {
		retval = ENOMEM;
		goto error;
	}

	/*
	 * We add 20 to whatever the caller requests, so he doesn't get
	 * burned by queueing things back to the pending sense queue.  In
	 * theory, there should probably only be one outstanding item, at
	 * most, on the pending sense queue for a LUN.  We'll clear the
	 * pending sense queue on the next command, whether or not it is
	 * a REQUEST SENSE.
	 */
	retval = ctl_pool_create(softc, port->port_name,
				 port->num_requested_ctl_io + 20, &pool);
	if (retval != 0) {
		free(port->wwpn_iid, M_CTL);
error:
		port->targ_port = -1;
		mtx_lock(&softc->ctl_lock);
		ctl_clear_mask(softc->ctl_port_mask, port_num);
		mtx_unlock(&softc->ctl_lock);
		return (retval);
	}
	port->targ_port = port_num;
	port->ctl_pool_ref = pool;
	if (port->options == NULL)
		port->options = nvlist_create(0);
	port->stats.item = port_num;
	mtx_init(&port->port_lock, "CTL port", NULL, MTX_DEF);

	mtx_lock(&softc->ctl_lock);
	STAILQ_INSERT_TAIL(&port->frontend->port_list, port, fe_links);
	for (tport = NULL, nport = STAILQ_FIRST(&softc->port_list);
	    nport != NULL && nport->targ_port < port_num;
	    tport = nport, nport = STAILQ_NEXT(tport, links)) {
	}
	if (tport)
		STAILQ_INSERT_AFTER(&softc->port_list, tport, port, links);
	else
		STAILQ_INSERT_HEAD(&softc->port_list, port, links);
	softc->ctl_ports[port->targ_port] = port;
	mtx_unlock(&softc->ctl_lock);

	return (retval);
}