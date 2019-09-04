#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  req; int /*<<< orphan*/  _link; } ;
typedef  TYPE_2__ h2o_http2_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  blocked_streams; } ;
struct TYPE_9__ {TYPE_1__ early_data; TYPE_4__* sock; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;
struct TYPE_10__ {int /*<<< orphan*/ * ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_replay_request_deferred (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_socket_ssl_is_early_data (TYPE_4__*) ; 

void h2o_http2_conn_register_for_replay(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    if (conn->sock->ssl != NULL && h2o_socket_ssl_is_early_data(conn->sock)) {
        h2o_linklist_insert(&conn->early_data.blocked_streams, &stream->_link);
    } else {
        h2o_replay_request_deferred(&stream->req);
    }
}