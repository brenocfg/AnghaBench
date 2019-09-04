#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ size; TYPE_5__* entries; } ;
struct TYPE_12__ {int /*<<< orphan*/  sending_link; TYPE_7__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
struct TYPE_9__ {int done; int /*<<< orphan*/ * proceed_req; } ;
struct st_h2o_http2client_stream_t {TYPE_6__* conn; TYPE_4__ output; TYPE_2__ super; TYPE_1__ streaming; } ;
struct TYPE_13__ {scalar_t__ len; } ;
typedef  TYPE_5__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_t ;
struct TYPE_11__ {int /*<<< orphan*/  sending_streams; } ;
struct TYPE_14__ {TYPE_3__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ ,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  request_write (TYPE_6__*) ; 

__attribute__((used)) static int do_write_req(h2o_httpclient_t *_client, h2o_iovec_t chunk, int is_end_stream)
{
    struct st_h2o_http2client_stream_t *stream = (void *)_client;
    assert(stream->streaming.proceed_req != NULL);

    if (is_end_stream)
        stream->streaming.done = 1;

    if (chunk.len != 0) {
        h2o_vector_reserve(stream->super.pool, &stream->output.data, stream->output.data.size + 1);
        stream->output.data.entries[stream->output.data.size++] = chunk;
    }

    if (!h2o_linklist_is_linked(&stream->output.sending_link)) {
        h2o_linklist_insert(&stream->conn->output.sending_streams, &stream->output.sending_link);
        request_write(stream->conn);
    }

    return 0;
}