#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct port {TYPE_1__* p_portal_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_portals; scalar_t__ pg_foreign; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 

int
port_is_dummy(struct port *port)
{

	if (port->p_portal_group) {
		if (port->p_portal_group->pg_foreign)
			return (1);
		if (TAILQ_EMPTY(&port->p_portal_group->pg_portals))
			return (1);
	}
	return (0);
}