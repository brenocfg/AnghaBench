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
struct sockaddr_hci {int /*<<< orphan*/  hci_node; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytes_sent; int /*<<< orphan*/  bytes_recv; int /*<<< orphan*/  sco_sent; int /*<<< orphan*/  sco_recv; int /*<<< orphan*/  acl_sent; int /*<<< orphan*/  acl_recv; int /*<<< orphan*/  evnt_recv; int /*<<< orphan*/  cmd_sent; } ;
struct TYPE_3__ {int /*<<< orphan*/  acl_free; int /*<<< orphan*/  acl_pkts; int /*<<< orphan*/  acl_size; int /*<<< orphan*/  sco_free; int /*<<< orphan*/  sco_pkts; int /*<<< orphan*/  sco_size; int /*<<< orphan*/  cmd_free; } ;
struct ng_btsocket_hci_raw_node_state {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_stat {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_role_switch {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_packet_mask {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_link_policy_mask {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_features {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_debug {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_buffer {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct ng_btsocket_hci_raw_node_bdaddr {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch; int /*<<< orphan*/  packet_mask; int /*<<< orphan*/  policy_mask; TYPE_2__ stat; TYPE_1__ buffer; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; } ;
struct bt_devinfo {int /*<<< orphan*/  debug; int /*<<< orphan*/  role_switch_info; int /*<<< orphan*/  packet_type_info; int /*<<< orphan*/  link_policy_info; int /*<<< orphan*/  bytes_sent; int /*<<< orphan*/  bytes_recv; int /*<<< orphan*/  sco_sent; int /*<<< orphan*/  sco_recv; int /*<<< orphan*/  acl_sent; int /*<<< orphan*/  acl_recv; int /*<<< orphan*/  evnt_recv; int /*<<< orphan*/  cmd_sent; int /*<<< orphan*/  acl_free; int /*<<< orphan*/  acl_pkts; int /*<<< orphan*/  acl_size; int /*<<< orphan*/  sco_free; int /*<<< orphan*/  sco_pkts; int /*<<< orphan*/  sco_size; int /*<<< orphan*/  cmd_free; int /*<<< orphan*/  features; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state; int /*<<< orphan*/  devname; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  ha ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_BDADDR ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_BUFFER ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_DEBUG ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_FEATURES ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_LINK_POLICY_MASK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_PACKET_MASK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_ROLE_SWITCH ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_STAT ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_STATE ; 
 int /*<<< orphan*/  bdaddr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_devclose (int) ; 
 int bt_devopen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_state*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
bt_devinfo(struct bt_devinfo *di)
{
	union {
		struct ng_btsocket_hci_raw_node_state		r0;
		struct ng_btsocket_hci_raw_node_bdaddr		r1;
		struct ng_btsocket_hci_raw_node_features	r2;
		struct ng_btsocket_hci_raw_node_buffer		r3;
		struct ng_btsocket_hci_raw_node_stat		r4;
		struct ng_btsocket_hci_raw_node_link_policy_mask r5;
		struct ng_btsocket_hci_raw_node_packet_mask	r6;
		struct ng_btsocket_hci_raw_node_role_switch	r7;
		struct ng_btsocket_hci_raw_node_debug		r8;
	}						rp;
	struct sockaddr_hci				ha;
	socklen_t					halen;
	int						s, rval;

	if (di == NULL) {
		errno = EINVAL;
		return (-1);
	}

	s = bt_devopen(di->devname);
	if (s < 0)
		return (-1);

	rval = -1;

	halen = sizeof(ha);
	if (getsockname(s, (struct sockaddr *) &ha, &halen) < 0)
		goto bad;
	strlcpy(di->devname, ha.hci_node, sizeof(di->devname));

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_STATE, &rp.r0, sizeof(rp.r0)) < 0)
		goto bad;
	di->state = rp.r0.state;

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_BDADDR, &rp.r1, sizeof(rp.r1)) < 0)
		goto bad;
	bdaddr_copy(&di->bdaddr, &rp.r1.bdaddr);
	
	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_FEATURES, &rp.r2, sizeof(rp.r2)) < 0)
		goto bad;
	memcpy(di->features, rp.r2.features, sizeof(di->features));

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_BUFFER, &rp.r3, sizeof(rp.r3)) < 0)
		goto bad;
	di->cmd_free = rp.r3.buffer.cmd_free;
	di->sco_size = rp.r3.buffer.sco_size;
	di->sco_pkts = rp.r3.buffer.sco_pkts;
	di->sco_free = rp.r3.buffer.sco_free;
	di->acl_size = rp.r3.buffer.acl_size;
	di->acl_pkts = rp.r3.buffer.acl_pkts;
	di->acl_free = rp.r3.buffer.acl_free;

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_STAT, &rp.r4, sizeof(rp.r4)) < 0)
		goto bad;
	di->cmd_sent = rp.r4.stat.cmd_sent;
	di->evnt_recv = rp.r4.stat.evnt_recv;
	di->acl_recv = rp.r4.stat.acl_recv;
	di->acl_sent = rp.r4.stat.acl_sent;
	di->sco_recv = rp.r4.stat.sco_recv;
	di->sco_sent = rp.r4.stat.sco_sent;
	di->bytes_recv = rp.r4.stat.bytes_recv;
	di->bytes_sent = rp.r4.stat.bytes_sent;

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_LINK_POLICY_MASK,
			&rp.r5, sizeof(rp.r5)) < 0)
		goto bad;
	di->link_policy_info = rp.r5.policy_mask;

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_PACKET_MASK,
			&rp.r6, sizeof(rp.r6)) < 0)
		goto bad;
	di->packet_type_info = rp.r6.packet_mask;

	 if (ioctl(s, SIOC_HCI_RAW_NODE_GET_ROLE_SWITCH,
			&rp.r7, sizeof(rp.r7)) < 0)
		goto bad;
	di->role_switch_info = rp.r7.role_switch;

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_DEBUG, &rp.r8, sizeof(rp.r8)) < 0)
		goto bad;
	di->debug = rp.r8.debug;

	rval = 0;
bad:
	bt_devclose(s);

	return (rval);
}