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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  fsts_id; int /*<<< orphan*/ * new_iface; int /*<<< orphan*/ * old_iface; } ;
struct fst_session {TYPE_1__ data; int /*<<< orphan*/  group; int /*<<< orphan*/  state; } ;
struct fst_ack_req {int /*<<< orphan*/  fsts_id; int /*<<< orphan*/  dialog_token; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FST_ACTION_ACK_REQUEST ; 
 int /*<<< orphan*/  FST_SESSION_STATE_TRANSITION_DONE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_group_assign_dialog_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_iface_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fst_printf_session (struct fst_session*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fst_printf_sframe (struct fst_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fst_session_is_ready (struct fst_session*) ; 
 int fst_session_send_action (struct fst_session*,int /*<<< orphan*/ ,struct fst_ack_req*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fst_session_set_state (struct fst_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fst_session_stt_arm (struct fst_session*) ; 
 int /*<<< orphan*/  host_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct fst_ack_req*,int /*<<< orphan*/ ,int) ; 

int fst_session_initiate_switch(struct fst_session *s)
{
	struct fst_ack_req req;
	int res;
	u8 dialog_token;

	if (!fst_session_is_ready(s)) {
		fst_printf_session(s, MSG_ERROR,
				   "cannot initiate switch due to wrong setup state (%d)",
				   s->state);
		return -1;
	}

	dialog_token = fst_group_assign_dialog_token(s->group);

	WPA_ASSERT(s->data.new_iface != NULL);
	WPA_ASSERT(s->data.old_iface != NULL);

	fst_printf_session(s, MSG_INFO, "initiating FST switch: %s => %s",
			   fst_iface_get_name(s->data.old_iface),
			   fst_iface_get_name(s->data.new_iface));

	os_memset(&req, 0, sizeof(req));

	req.action = FST_ACTION_ACK_REQUEST;
	req.dialog_token = dialog_token;
	req.fsts_id = host_to_le32(s->data.fsts_id);

	res = fst_session_send_action(s, FALSE, &req, sizeof(req), NULL);
	if (!res) {
		fst_printf_sframe(s, FALSE, MSG_INFO, "FST Ack Request sent");
		fst_session_set_state(s, FST_SESSION_STATE_TRANSITION_DONE,
				      NULL);
		fst_session_stt_arm(s);
	} else {
		fst_printf_sframe(s, FALSE, MSG_ERROR,
				  "Cannot send FST Ack Request");
	}

	return res;
}