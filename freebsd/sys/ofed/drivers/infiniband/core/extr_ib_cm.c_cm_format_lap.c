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
typedef  scalar_t__ u8 ;
struct ib_sa_path_rec {int /*<<< orphan*/  packet_life_time; int /*<<< orphan*/  sl; int /*<<< orphan*/  rate; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  slid; } ;
struct cm_lap_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  alt_hop_limit; int /*<<< orphan*/  alt_remote_gid; int /*<<< orphan*/  alt_local_gid; int /*<<< orphan*/  alt_remote_lid; int /*<<< orphan*/  alt_local_lid; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  hdr; } ;
struct TYPE_8__ {TYPE_3__* port; } ;
struct TYPE_5__ {int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct cm_id_private {TYPE_4__ av; int /*<<< orphan*/  remote_qpn; TYPE_1__ id; } ;
struct TYPE_7__ {TYPE_2__* cm_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  ack_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_LAP_ATTR_ID ; 
 int /*<<< orphan*/  CM_MSG_SEQUENCE_LAP ; 
 int /*<<< orphan*/  cm_ack_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_form_tid (struct cm_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_lap_set_flow_label (struct cm_lap_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_lap_set_local_ack_timeout (struct cm_lap_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_lap_set_packet_rate (struct cm_lap_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_lap_set_remote_qpn (struct cm_lap_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_lap_set_remote_resp_timeout (struct cm_lap_msg*,int) ; 
 int /*<<< orphan*/  cm_lap_set_sl (struct cm_lap_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_lap_set_subnet_local (struct cm_lap_msg*,int) ; 
 int /*<<< orphan*/  cm_lap_set_traffic_class (struct cm_lap_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static void cm_format_lap(struct cm_lap_msg *lap_msg,
			  struct cm_id_private *cm_id_priv,
			  struct ib_sa_path_rec *alternate_path,
			  const void *private_data,
			  u8 private_data_len)
{
	cm_format_mad_hdr(&lap_msg->hdr, CM_LAP_ATTR_ID,
			  cm_form_tid(cm_id_priv, CM_MSG_SEQUENCE_LAP));
	lap_msg->local_comm_id = cm_id_priv->id.local_id;
	lap_msg->remote_comm_id = cm_id_priv->id.remote_id;
	cm_lap_set_remote_qpn(lap_msg, cm_id_priv->remote_qpn);
	/* todo: need remote CM response timeout */
	cm_lap_set_remote_resp_timeout(lap_msg, 0x1F);
	lap_msg->alt_local_lid = alternate_path->slid;
	lap_msg->alt_remote_lid = alternate_path->dlid;
	lap_msg->alt_local_gid = alternate_path->sgid;
	lap_msg->alt_remote_gid = alternate_path->dgid;
	cm_lap_set_flow_label(lap_msg, alternate_path->flow_label);
	cm_lap_set_traffic_class(lap_msg, alternate_path->traffic_class);
	lap_msg->alt_hop_limit = alternate_path->hop_limit;
	cm_lap_set_packet_rate(lap_msg, alternate_path->rate);
	cm_lap_set_sl(lap_msg, alternate_path->sl);
	cm_lap_set_subnet_local(lap_msg, 1); /* local only... */
	cm_lap_set_local_ack_timeout(lap_msg,
		cm_ack_timeout(cm_id_priv->av.port->cm_dev->ack_delay,
			       alternate_path->packet_life_time));

	if (private_data && private_data_len)
		memcpy(lap_msg->private_data, private_data, private_data_len);
}