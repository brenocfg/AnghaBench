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
struct ctl_softc {int /*<<< orphan*/  othersc_pool; } ;
struct ctl_port {struct ctl_port* port_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 scalar_t__ CTL_HA_STATUS_SUCCESS ; 
 int EIO ; 
 int /*<<< orphan*/  M_CTL ; 
 struct ctl_port* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct ctl_softc* control_softc ; 
 scalar_t__ ctl_ha_msg_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_ha_msg_destroy (struct ctl_softc*) ; 
 int /*<<< orphan*/  ctl_ha_msg_shutdown (struct ctl_softc*) ; 
 int /*<<< orphan*/  ctl_pool_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_port_deregister (struct ctl_port*) ; 
 int /*<<< orphan*/  free (struct ctl_port*,int /*<<< orphan*/ ) ; 
 TYPE_1__ ha_frontend ; 

__attribute__((used)) static int
ctl_ha_shutdown(void)
{
	struct ctl_softc *softc = control_softc;
	struct ctl_port *port;

	ctl_ha_msg_shutdown(softc);
	if (ctl_ha_msg_deregister(CTL_HA_CHAN_CTL) != CTL_HA_STATUS_SUCCESS)
		return (EIO);
	if (ctl_ha_msg_destroy(softc) != CTL_HA_STATUS_SUCCESS)
		return (EIO);
	ctl_pool_free(softc->othersc_pool);
	while ((port = STAILQ_FIRST(&ha_frontend.port_list)) != NULL) {
		ctl_port_deregister(port);
		free(port->port_name, M_CTL);
		free(port, M_CTL);
	}
	return (0);
}