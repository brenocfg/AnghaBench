#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_21__ ;
typedef  struct TYPE_38__   TYPE_20__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_19__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_17__ ;
typedef  struct TYPE_33__   TYPE_16__ ;
typedef  struct TYPE_32__   TYPE_15__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct st_quicly_conn_streamgroup_state_t {int next_stream_id; int /*<<< orphan*/  num_streams; } ;
struct TYPE_32__ {int /*<<< orphan*/  control; } ;
struct TYPE_33__ {TYPE_15__ pending_link; } ;
struct TYPE_36__ {int stream_id; int streams_blocked; TYPE_16__ _send_aux; } ;
typedef  TYPE_19__ quicly_stream_t ;
struct TYPE_46__ {int uni; int bidi_remote; } ;
struct TYPE_47__ {TYPE_8__ max_stream_data; } ;
struct TYPE_27__ {TYPE_9__ transport_params; } ;
struct TYPE_40__ {struct st_quicly_conn_streamgroup_state_t bidi; struct st_quicly_conn_streamgroup_state_t uni; } ;
struct TYPE_35__ {TYPE_17__* ctx; TYPE_10__ peer; TYPE_2__ host; } ;
struct TYPE_28__ {int /*<<< orphan*/  prev; } ;
struct TYPE_29__ {TYPE_11__ bidi; TYPE_11__ uni; } ;
struct TYPE_30__ {TYPE_12__ blocked; } ;
struct TYPE_31__ {TYPE_13__ streams; } ;
struct TYPE_41__ {int count; } ;
struct TYPE_37__ {int count; } ;
struct TYPE_42__ {TYPE_3__ bidi; TYPE_1__ uni; } ;
struct TYPE_43__ {TYPE_4__ max_streams; } ;
struct TYPE_38__ {TYPE_18__ super; TYPE_14__ pending; TYPE_5__ egress; } ;
typedef  TYPE_20__ quicly_conn_t ;
struct TYPE_44__ {scalar_t__ bidi_local; } ;
struct TYPE_45__ {TYPE_6__ max_stream_data; } ;
struct TYPE_39__ {int (* cb ) (TYPE_21__*,TYPE_19__*) ;} ;
struct TYPE_34__ {TYPE_21__* stream_open; TYPE_7__ transport_params; } ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 TYPE_19__* open_stream (TYPE_20__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  quicly_linklist_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_21__*,TYPE_19__*) ; 

int quicly_open_stream(quicly_conn_t *conn, quicly_stream_t **_stream, int uni)
{
    quicly_stream_t *stream;
    struct st_quicly_conn_streamgroup_state_t *group;
    uint64_t *max_stream_count;
    uint32_t max_stream_data_local;
    uint64_t max_stream_data_remote;
    int ret;

    /* determine the states */
    if (uni) {
        group = &conn->super.host.uni;
        max_stream_count = &conn->egress.max_streams.uni.count;
        max_stream_data_local = 0;
        max_stream_data_remote = conn->super.peer.transport_params.max_stream_data.uni;
    } else {
        group = &conn->super.host.bidi;
        max_stream_count = &conn->egress.max_streams.bidi.count;
        max_stream_data_local = (uint32_t)conn->super.ctx->transport_params.max_stream_data.bidi_local;
        max_stream_data_remote = conn->super.peer.transport_params.max_stream_data.bidi_remote;
    }

    /* open */
    if ((stream = open_stream(conn, group->next_stream_id, max_stream_data_local, max_stream_data_remote)) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    ++group->num_streams;
    group->next_stream_id += 4;

    /* adjust blocked */
    if (stream->stream_id / 4 >= *max_stream_count) {
        stream->streams_blocked = 1;
        quicly_linklist_insert((uni ? &conn->pending.streams.blocked.uni : &conn->pending.streams.blocked.bidi)->prev,
                               &stream->_send_aux.pending_link.control);
    }

    /* application-layer initialization */
    if ((ret = conn->super.ctx->stream_open->cb(conn->super.ctx->stream_open, stream)) != 0)
        return ret;

    *_stream = stream;
    return 0;
}