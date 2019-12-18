#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct port {struct port* p_name; TYPE_2__* p_conf; TYPE_1__* p_target; TYPE_4__* p_pport; TYPE_3__* p_portal_group; } ;
struct TYPE_8__ {int /*<<< orphan*/  pp_ports; } ;
struct TYPE_7__ {int /*<<< orphan*/  pg_ports; } ;
struct TYPE_6__ {int /*<<< orphan*/  conf_ports; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct port*) ; 
 int /*<<< orphan*/  p_next ; 
 int /*<<< orphan*/  p_pgs ; 
 int /*<<< orphan*/  p_pps ; 
 int /*<<< orphan*/  p_ts ; 

void
port_delete(struct port *port)
{

	if (port->p_portal_group)
		TAILQ_REMOVE(&port->p_portal_group->pg_ports, port, p_pgs);
	if (port->p_pport)
		TAILQ_REMOVE(&port->p_pport->pp_ports, port, p_pps);
	if (port->p_target)
		TAILQ_REMOVE(&port->p_target->t_ports, port, p_ts);
	TAILQ_REMOVE(&port->p_conf->conf_ports, port, p_next);
	free(port->p_name);
	free(port);
}