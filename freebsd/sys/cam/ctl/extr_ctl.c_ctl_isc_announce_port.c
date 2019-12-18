#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int lun_map_len; int port_devid_len; int target_devid_len; int init_devid_len; int /*<<< orphan*/ * data; scalar_t__ name_len; int /*<<< orphan*/  status; int /*<<< orphan*/  virtual_port; int /*<<< orphan*/  physical_port; int /*<<< orphan*/  port_type; } ;
struct TYPE_8__ {scalar_t__ targ_port; } ;
struct TYPE_9__ {TYPE_1__ nexus; int /*<<< orphan*/  msg_type; } ;
union ctl_ha_msg {TYPE_6__ port; TYPE_2__ hdr; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ctl_softc {scalar_t__ port_min; scalar_t__ port_max; scalar_t__ ha_link; int ha_id; } ;
struct ctl_port {scalar_t__ targ_port; char* port_name; int lun_map_size; TYPE_5__* init_devid; TYPE_4__* target_devid; TYPE_3__* port_devid; int /*<<< orphan*/  lun_map; int /*<<< orphan*/  status; int /*<<< orphan*/  virtual_port; int /*<<< orphan*/  physical_port; int /*<<< orphan*/  port_type; struct ctl_softc* ctl_softc; } ;
struct TYPE_12__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 scalar_t__ CTL_HA_LINK_ONLINE ; 
 int /*<<< orphan*/  CTL_MSG_PORT_SYNC ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bzero (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ctl_ha_msg_send (int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (union ctl_ha_msg*,int /*<<< orphan*/ ) ; 
 union ctl_ha_msg* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sprintf (int /*<<< orphan*/ *,char*,int,char*) ; 
 int strlen (char*) ; 

void
ctl_isc_announce_port(struct ctl_port *port)
{
	struct ctl_softc *softc = port->ctl_softc;
	union ctl_ha_msg *msg;
	int i;

	if (port->targ_port < softc->port_min ||
	    port->targ_port >= softc->port_max ||
	    softc->ha_link != CTL_HA_LINK_ONLINE)
		return;
	i = sizeof(msg->port) + strlen(port->port_name) + 1;
	if (port->lun_map)
		i += port->lun_map_size * sizeof(uint32_t);
	if (port->port_devid)
		i += port->port_devid->len;
	if (port->target_devid)
		i += port->target_devid->len;
	if (port->init_devid)
		i += port->init_devid->len;
	msg = malloc(i, M_CTL, M_WAITOK);
	bzero(&msg->port, sizeof(msg->port));
	msg->hdr.msg_type = CTL_MSG_PORT_SYNC;
	msg->hdr.nexus.targ_port = port->targ_port;
	msg->port.port_type = port->port_type;
	msg->port.physical_port = port->physical_port;
	msg->port.virtual_port = port->virtual_port;
	msg->port.status = port->status;
	i = 0;
	msg->port.name_len = sprintf(&msg->port.data[i],
	    "%d:%s", softc->ha_id, port->port_name) + 1;
	i += msg->port.name_len;
	if (port->lun_map) {
		msg->port.lun_map_len = port->lun_map_size * sizeof(uint32_t);
		memcpy(&msg->port.data[i], port->lun_map,
		    msg->port.lun_map_len);
		i += msg->port.lun_map_len;
	}
	if (port->port_devid) {
		msg->port.port_devid_len = port->port_devid->len;
		memcpy(&msg->port.data[i], port->port_devid->data,
		    msg->port.port_devid_len);
		i += msg->port.port_devid_len;
	}
	if (port->target_devid) {
		msg->port.target_devid_len = port->target_devid->len;
		memcpy(&msg->port.data[i], port->target_devid->data,
		    msg->port.target_devid_len);
		i += msg->port.target_devid_len;
	}
	if (port->init_devid) {
		msg->port.init_devid_len = port->init_devid->len;
		memcpy(&msg->port.data[i], port->init_devid->data,
		    msg->port.init_devid_len);
		i += msg->port.init_devid_len;
	}
	ctl_ha_msg_send(CTL_HA_CHAN_CTL, &msg->port, sizeof(msg->port) + i,
	    M_WAITOK);
	free(msg, M_CTL);
}