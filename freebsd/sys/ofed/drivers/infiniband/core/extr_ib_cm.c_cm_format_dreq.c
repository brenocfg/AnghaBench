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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct cm_id_private {int /*<<< orphan*/  remote_qpn; TYPE_1__ id; } ;
struct cm_dreq_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DREQ_ATTR_ID ; 
 int /*<<< orphan*/  CM_MSG_SEQUENCE_DREQ ; 
 int /*<<< orphan*/  cm_dreq_set_remote_qpn (struct cm_dreq_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_form_tid (struct cm_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static void cm_format_dreq(struct cm_dreq_msg *dreq_msg,
			  struct cm_id_private *cm_id_priv,
			  const void *private_data,
			  u8 private_data_len)
{
	cm_format_mad_hdr(&dreq_msg->hdr, CM_DREQ_ATTR_ID,
			  cm_form_tid(cm_id_priv, CM_MSG_SEQUENCE_DREQ));
	dreq_msg->local_comm_id = cm_id_priv->id.local_id;
	dreq_msg->remote_comm_id = cm_id_priv->id.remote_id;
	cm_dreq_set_remote_qpn(dreq_msg, cm_id_priv->remote_qpn);

	if (private_data && private_data_len)
		memcpy(dreq_msg->private_data, private_data, private_data_len);
}