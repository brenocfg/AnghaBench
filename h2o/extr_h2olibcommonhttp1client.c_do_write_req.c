#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http1client_t {int _body_buf_is_done; int /*<<< orphan*/  sock; scalar_t__ _is_chunked; TYPE_2__* _body_buf_in_flight; int /*<<< orphan*/ * _body_buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_t ;
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t encode_chunk (struct st_h2o_http1client_t*,TYPE_1__*,TYPE_1__) ; 
 scalar_t__ h2o_buffer_append (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_1__ h2o_iovec_init (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 scalar_t__ h2o_socket_is_writing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  on_req_body_done (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_buffers (int /*<<< orphan*/ **,TYPE_2__**) ; 

__attribute__((used)) static int do_write_req(h2o_httpclient_t *_client, h2o_iovec_t chunk, int is_end_stream)
{
    struct st_h2o_http1client_t *client = (struct st_h2o_http1client_t *)_client;

    client->_body_buf_is_done = is_end_stream;

    if (client->_body_buf == NULL)
        h2o_buffer_init(&client->_body_buf, &h2o_socket_buffer_prototype);

    if (chunk.len != 0) {
        if (h2o_buffer_append(&client->_body_buf, chunk.base, chunk.len) == 0)
            return -1;
    }

    if (h2o_socket_is_writing(client->sock))
        return 0;

    assert(client->_body_buf_in_flight == NULL || client->_body_buf_in_flight->size == 0);

    swap_buffers(&client->_body_buf, &client->_body_buf_in_flight);

    if (client->_body_buf_in_flight->size == 0) {
        /* return immediately if the chunk is empty */
        on_req_body_done(client->sock, NULL);
        return 0;
    }

    h2o_iovec_t iov = h2o_iovec_init(client->_body_buf_in_flight->bytes, client->_body_buf_in_flight->size);
    if (client->_is_chunked) {
        h2o_iovec_t bufs[3];
        size_t bufcnt = encode_chunk(client, bufs, iov);
        h2o_socket_write(client->sock, bufs, bufcnt, on_req_body_done);
    } else {
        h2o_socket_write(client->sock, &iov, 1, on_req_body_done);
    }
    return 0;
}