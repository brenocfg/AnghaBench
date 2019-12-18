#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  node; } ;
struct TYPE_8__ {TYPE_6__ ref; } ;
struct st_h2o_http3_server_stream_t {TYPE_1__ scheduler; } ;
struct TYPE_9__ {int /*<<< orphan*/  quic; } ;
struct st_h2o_http3_server_conn_t {TYPE_2__ h3; } ;
struct TYPE_10__ {struct st_h2o_http3_server_stream_t* data; } ;
typedef  TYPE_3__ quicly_stream_t ;
typedef  int int64_t ;
typedef  int h2o_http3_priority_element_type_t ;
struct TYPE_11__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_4__ h2o_http2_scheduler_openref_t ;
typedef  int /*<<< orphan*/  h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_FRAME ; 
 int H2O_HTTP3_ERROR_GENERAL_PROTOCOL ; 
#define  H2O_HTTP3_PRIORITY_ELEMENT_TYPE_PLACEHOLDER 131 
#define  H2O_HTTP3_PRIORITY_ELEMENT_TYPE_PUSH_STREAM 130 
#define  H2O_HTTP3_PRIORITY_ELEMENT_TYPE_REQUEST_STREAM 129 
#define  H2O_HTTP3_PRIORITY_ELEMENT_TYPE_ROOT 128 
 int H2O_HTTP3_SETTINGS_NUM_PLACEHOLDERS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* get_freestanding_scheduler_ref (struct st_h2o_http3_server_conn_t*,int,int) ; 
 int /*<<< orphan*/ * get_orphan_placeholder (struct st_h2o_http3_server_conn_t*) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_is_open (TYPE_6__*) ; 
 int quicly_get_ingress_max_streams (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int quicly_get_peer_next_stream_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* quicly_get_stream (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quicly_stream_is_client_initiated (int) ; 
 int /*<<< orphan*/  quicly_stream_is_unidirectional (int) ; 

__attribute__((used)) static int get_scheduler_node(struct st_h2o_http3_server_conn_t *conn, h2o_http2_scheduler_node_t **node,
                              h2o_http3_priority_element_type_t type, int64_t id, h2o_http2_scheduler_node_t *root,
                              const char **err_desc)
{
    switch (type) {
    case H2O_HTTP3_PRIORITY_ELEMENT_TYPE_REQUEST_STREAM: {

        /* Return the scheduler node of an existing request stream, or create a queued entry and returns that */
        quicly_stream_t *qs;
        if (!(quicly_stream_is_client_initiated(id) && !quicly_stream_is_unidirectional(id) &&
              id / 4 < quicly_get_ingress_max_streams(conn->h3.quic, 0))) {
            *err_desc = "invalid request stream id in PRIORITY frame";
            return H2O_HTTP3_ERROR_FRAME;
        }
        if ((qs = quicly_get_stream(conn->h3.quic, id)) != NULL) {
            struct st_h2o_http3_server_stream_t *stream = qs->data;
            assert(stream != NULL);
            assert(h2o_http2_scheduler_is_open(&stream->scheduler.ref));
            *node = &stream->scheduler.ref.node;
        } else {
            h2o_http2_scheduler_openref_t *ref =
                get_freestanding_scheduler_ref(conn, id, id >= quicly_get_peer_next_stream_id(conn->h3.quic, 0));
            /* ref being NULL means that the stream has been closed and the PRIORITY information is no longer available */
            *node = ref != NULL ? &ref->node : get_orphan_placeholder(conn);
        }

    } break;

    case H2O_HTTP3_PRIORITY_ELEMENT_TYPE_PUSH_STREAM:
        *err_desc = "unexpectedly found a push stream id in PRIORITY frame";
        return H2O_HTTP3_ERROR_GENERAL_PROTOCOL;

    case H2O_HTTP3_PRIORITY_ELEMENT_TYPE_PLACEHOLDER:
        /* return a placeholder, initializing it to the default values if it is not open yet */
        if (id >= H2O_HTTP3_SETTINGS_NUM_PLACEHOLDERS) {
            *err_desc = "invalid placeholder id found in PRIORITY frame";
            return H2O_HTTP3_ERROR_FRAME;
        }
        *node = &get_freestanding_scheduler_ref(conn, -1 - id, 1)->node;
        break;

    case H2O_HTTP3_PRIORITY_ELEMENT_TYPE_ROOT:
        if (root == NULL) {
            *err_desc = "invalid depedency type in PRIORITY frame";
            return H2O_HTTP3_ERROR_FRAME;
        }
        *node = root;
        break;
    }

    return 0;
}