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
struct TYPE_8__ {int stream_id; int /*<<< orphan*/  req; int /*<<< orphan*/ * req_body; int /*<<< orphan*/ * cache_digests; } ;
typedef  TYPE_1__ h2o_http2_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/ * _http1_req_input; } ;
typedef  TYPE_2__ h2o_http2_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_cache_digests_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_dispose_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_conn_unregister_stream (TYPE_2__*,TYPE_1__*) ; 

void h2o_http2_stream_close(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    h2o_http2_conn_unregister_stream(conn, stream);
    if (stream->cache_digests != NULL)
        h2o_cache_digests_destroy(stream->cache_digests);
    if (stream->req_body != NULL)
        h2o_buffer_dispose(&stream->req_body);
    h2o_dispose_request(&stream->req);
    if (stream->stream_id == 1 && conn->_http1_req_input != NULL)
        h2o_buffer_dispose(&conn->_http1_req_input);
    free(stream);
}