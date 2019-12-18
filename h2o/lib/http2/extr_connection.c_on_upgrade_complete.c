#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_8__* input; TYPE_2__* data; } ;
typedef  TYPE_1__ h2o_socket_t ;
struct TYPE_13__ {TYPE_1__* sock; TYPE_8__* _http1_req_input; } ;
typedef  TYPE_2__ h2o_http2_conn_t ;
struct TYPE_14__ {size_t size; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  execute_or_enqueue_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_8__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_reserve (TYPE_8__**,size_t) ; 
 int /*<<< orphan*/  h2o_http2_conn_get_stream (TYPE_2__*,int) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_1__*,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  on_read (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_upgrade_complete(void *_conn, h2o_socket_t *sock, size_t reqsize)
{
    h2o_http2_conn_t *conn = _conn;

    if (sock == NULL) {
        close_connection(conn);
        return;
    }

    conn->sock = sock;
    sock->data = conn;
    conn->_http1_req_input = sock->input;
    h2o_buffer_init(&sock->input, &h2o_socket_buffer_prototype);

    /* setup inbound */
    h2o_socket_read_start(conn->sock, on_read);

    /* handle the request */
    execute_or_enqueue_request(conn, h2o_http2_conn_get_stream(conn, 1));

    if (conn->_http1_req_input->size > reqsize) {
        size_t remaining_bytes = conn->_http1_req_input->size - reqsize;
        h2o_buffer_reserve(&sock->input, remaining_bytes);
        memcpy(sock->input->bytes, conn->_http1_req_input->bytes + reqsize, remaining_bytes);
        sock->input->size += remaining_bytes;
        on_read(conn->sock, NULL);
    }
}