#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sending_link; int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {int done; int /*<<< orphan*/ * proceed_req; } ;
struct st_h2o_http2client_stream_t {TYPE_5__* conn; TYPE_3__ output; TYPE_1__ streaming; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_t ;
struct TYPE_8__ {int /*<<< orphan*/  sending_streams; } ;
struct TYPE_11__ {TYPE_2__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_append (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  request_write (TYPE_5__*) ; 

__attribute__((used)) static int do_write_req(h2o_httpclient_t *_client, h2o_iovec_t chunk, int is_end_stream)
{
    struct st_h2o_http2client_stream_t *stream = (void *)_client;
    assert(stream->streaming.proceed_req != NULL);

    if (is_end_stream)
        stream->streaming.done = 1;

    if (stream->output.buf == NULL) {
        h2o_buffer_init(&stream->output.buf, &h2o_socket_buffer_prototype);
    }

    if (chunk.len != 0) {
        h2o_buffer_append(&stream->output.buf, chunk.base, chunk.len);
    }

    if (!h2o_linklist_is_linked(&stream->output.sending_link)) {
        h2o_linklist_insert(&stream->conn->output.sending_streams, &stream->output.sending_link);
        request_write(stream->conn);
    }

    return 0;
}