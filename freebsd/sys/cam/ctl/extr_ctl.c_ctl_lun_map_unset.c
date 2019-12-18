#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct ctl_port {size_t* lun_map; size_t lun_map_size; int status; int /*<<< orphan*/  targ_lun_arg; int /*<<< orphan*/  (* lun_disable ) (int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int CTL_PORT_STATUS_ONLINE ; 
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  ctl_isc_announce_port (struct ctl_port*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t) ; 

int
ctl_lun_map_unset(struct ctl_port *port, uint32_t plun)
{
	uint32_t old;

	if (port->lun_map == NULL || plun >= port->lun_map_size)
		return (0);
	old = port->lun_map[plun];
	port->lun_map[plun] = UINT32_MAX;
	if ((port->status & CTL_PORT_STATUS_ONLINE) && old != UINT32_MAX) {
		if (port->lun_disable != NULL)
			port->lun_disable(port->targ_lun_arg, plun);
		ctl_isc_announce_port(port);
	}
	return (0);
}