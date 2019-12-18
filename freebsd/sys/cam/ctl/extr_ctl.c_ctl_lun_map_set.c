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
struct ctl_port {size_t* lun_map; size_t lun_map_size; int status; int /*<<< orphan*/  targ_lun_arg; int /*<<< orphan*/  (* lun_enable ) (int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int CTL_PORT_STATUS_ONLINE ; 
 int EINVAL ; 
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  ctl_isc_announce_port (struct ctl_port*) ; 
 int ctl_lun_map_init (struct ctl_port*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t) ; 

int
ctl_lun_map_set(struct ctl_port *port, uint32_t plun, uint32_t glun)
{
	int status;
	uint32_t old;

	if (port->lun_map == NULL) {
		status = ctl_lun_map_init(port);
		if (status != 0)
			return (status);
	}
	if (plun >= port->lun_map_size)
		return (EINVAL);
	old = port->lun_map[plun];
	port->lun_map[plun] = glun;
	if ((port->status & CTL_PORT_STATUS_ONLINE) && old == UINT32_MAX) {
		if (port->lun_enable != NULL)
			port->lun_enable(port->targ_lun_arg, plun);
		ctl_isc_announce_port(port);
	}
	return (0);
}