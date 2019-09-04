#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wslay_event_context_ptr ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* sock; int /*<<< orphan*/  ws_ctx; } ;
typedef  TYPE_2__ h2o_websocket_conn_t ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/  bytes; } ;
struct TYPE_4__ {TYPE_3__* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSLAY_ERR_WOULDBLOCK ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_3__**,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wslay_event_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t recv_callback(wslay_event_context_ptr ctx, uint8_t *buf, size_t len, int flags, void *_conn)
{
    h2o_websocket_conn_t *conn = _conn;

    /* return WOULDBLOCK if no data */
    if (conn->sock->input->size == 0) {
        wslay_event_set_error(conn->ws_ctx, WSLAY_ERR_WOULDBLOCK);
        return -1;
    }

    if (conn->sock->input->size < len)
        len = conn->sock->input->size;
    memcpy(buf, conn->sock->input->bytes, len);
    h2o_buffer_consume(&conn->sock->input, len);
    return len;
}