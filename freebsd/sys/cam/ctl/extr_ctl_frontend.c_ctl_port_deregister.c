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
struct ctl_softc {int /*<<< orphan*/  ctl_lock; int /*<<< orphan*/ ** ctl_ports; int /*<<< orphan*/  ctl_port_mask; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  port_list; } ;
struct ctl_port {int targ_port; int max_initiators; int /*<<< orphan*/  port_lock; TYPE_2__* wwpn_iid; TYPE_2__* init_devid; TYPE_2__* target_devid; TYPE_2__* port_devid; int /*<<< orphan*/  options; TYPE_1__* frontend; scalar_t__ ctl_pool_ref; struct ctl_softc* ctl_softc; } ;
struct ctl_io_pool {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct ctl_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_clear_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctl_lun_map_deinit (struct ctl_port*) ; 
 int /*<<< orphan*/  ctl_pool_free (struct ctl_io_pool*) ; 
 int /*<<< orphan*/  ctl_port ; 
 int /*<<< orphan*/  fe_links ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ ) ; 

int
ctl_port_deregister(struct ctl_port *port)
{
	struct ctl_softc *softc = port->ctl_softc;
	struct ctl_io_pool *pool = (struct ctl_io_pool *)port->ctl_pool_ref;
	int i;

	if (port->targ_port == -1)
		return (1);

	mtx_lock(&softc->ctl_lock);
	STAILQ_REMOVE(&softc->port_list, port, ctl_port, links);
	STAILQ_REMOVE(&port->frontend->port_list, port, ctl_port, fe_links);
	softc->num_ports--;
	ctl_clear_mask(softc->ctl_port_mask, port->targ_port);
	softc->ctl_ports[port->targ_port] = NULL;
	mtx_unlock(&softc->ctl_lock);

	ctl_pool_free(pool);
	nvlist_destroy(port->options);

	ctl_lun_map_deinit(port);
	free(port->port_devid, M_CTL);
	port->port_devid = NULL;
	free(port->target_devid, M_CTL);
	port->target_devid = NULL;
	free(port->init_devid, M_CTL);
	port->init_devid = NULL;
	for (i = 0; i < port->max_initiators; i++)
		free(port->wwpn_iid[i].name, M_CTL);
	free(port->wwpn_iid, M_CTL);
	mtx_destroy(&port->port_lock);

	return (0);
}