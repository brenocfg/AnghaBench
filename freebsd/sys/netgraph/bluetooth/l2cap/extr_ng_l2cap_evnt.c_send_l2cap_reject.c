#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  ng_l2cap_con_p ;
typedef  TYPE_1__* ng_l2cap_cmd_p ;
struct TYPE_5__ {int /*<<< orphan*/ * aux; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NG_L2CAP_CMD_REJ ; 
 int /*<<< orphan*/  _ng_l2cap_cmd_rej (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_l2cap_free_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_l2cap_link_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ng_l2cap_lp_deliver (int /*<<< orphan*/ ) ; 
 TYPE_1__* ng_l2cap_new_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_l2cap_reject(ng_l2cap_con_p con, u_int8_t ident, u_int16_t reason,
		u_int16_t mtu, u_int16_t scid, u_int16_t dcid)
{
	ng_l2cap_cmd_p	cmd = NULL;

	cmd = ng_l2cap_new_cmd(con, NULL, ident, NG_L2CAP_CMD_REJ, 0);
	if (cmd == NULL)
		return (ENOMEM);

	 _ng_l2cap_cmd_rej(cmd->aux, cmd->ident, reason, mtu, scid, dcid);
	if (cmd->aux == NULL) {
		ng_l2cap_free_cmd(cmd);

		return (ENOBUFS);
	}

	/* Link command to the queue */
	ng_l2cap_link_cmd(con, cmd);
	ng_l2cap_lp_deliver(con);

	return (0);
}