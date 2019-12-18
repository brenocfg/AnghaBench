#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wslay_event_on_msg_recv_arg {int /*<<< orphan*/  msg_length; int /*<<< orphan*/  msg; int /*<<< orphan*/  opcode; } ;
struct wslay_event_msg {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  ws_ctx; } ;
typedef  TYPE_1__ h2o_websocket_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_websocket_close (TYPE_1__*) ; 
 int /*<<< orphan*/  wslay_event_queue_msg (int /*<<< orphan*/ ,struct wslay_event_msg*) ; 
 int /*<<< orphan*/  wslay_is_ctrl_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_ws_message(h2o_websocket_conn_t *conn, const struct wslay_event_on_msg_recv_arg *arg)
{
    if (arg == NULL) {
        h2o_websocket_close(conn);
        return;
    }

    if (!wslay_is_ctrl_frame(arg->opcode)) {
        struct wslay_event_msg msgarg = {arg->opcode, arg->msg, arg->msg_length};
        wslay_event_queue_msg(conn->ws_ctx, &msgarg);
    }
}