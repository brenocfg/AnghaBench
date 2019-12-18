#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct st_quicly_conn_streamgroup_state_t {int next_stream_id; scalar_t__ num_streams; } ;
struct TYPE_27__ {int uni; int /*<<< orphan*/  args; } ;
struct TYPE_28__ {TYPE_7__ max_streams; } ;
struct TYPE_29__ {TYPE_8__ data; } ;
typedef  TYPE_9__ quicly_sent_t ;
struct TYPE_19__ {int /*<<< orphan*/  dst; } ;
typedef  TYPE_10__ quicly_send_context_t ;
typedef  int /*<<< orphan*/  quicly_maxsender_t ;
struct TYPE_23__ {struct st_quicly_conn_streamgroup_state_t bidi; struct st_quicly_conn_streamgroup_state_t uni; } ;
struct TYPE_26__ {TYPE_5__* ctx; TYPE_3__ peer; } ;
struct TYPE_21__ {int /*<<< orphan*/ * bidi; int /*<<< orphan*/ * uni; } ;
struct TYPE_22__ {TYPE_1__ max_streams; } ;
struct TYPE_20__ {TYPE_6__ super; TYPE_2__ ingress; } ;
typedef  TYPE_11__ quicly_conn_t ;
struct TYPE_24__ {scalar_t__ max_streams_bidi; scalar_t__ max_streams_uni; } ;
struct TYPE_25__ {TYPE_4__ transport_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_STREAMS_SEND ; 
 int /*<<< orphan*/  QUICLY_MAX_STREAMS_FRAME_CAPACITY ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int allocate_ack_eliciting_frame (TYPE_11__*,TYPE_10__*,int /*<<< orphan*/ ,TYPE_9__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_ack_max_streams ; 
 int /*<<< orphan*/  probe_now () ; 
 int /*<<< orphan*/  quicly_encode_max_streams_frame (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  quicly_maxsender_record (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  should_send_max_streams (TYPE_11__*,int) ; 

__attribute__((used)) static int send_max_streams(quicly_conn_t *conn, int uni, quicly_send_context_t *s)
{
    if (!should_send_max_streams(conn, uni))
        return 0;

    quicly_maxsender_t *maxsender = uni ? conn->ingress.max_streams.uni : conn->ingress.max_streams.bidi;
    struct st_quicly_conn_streamgroup_state_t *group = uni ? &conn->super.peer.uni : &conn->super.peer.bidi;
    int ret;

    uint64_t new_count =
        group->next_stream_id / 4 +
        (uni ? conn->super.ctx->transport_params.max_streams_uni : conn->super.ctx->transport_params.max_streams_bidi) -
        group->num_streams;

    quicly_sent_t *sent;
    if ((ret = allocate_ack_eliciting_frame(conn, s, QUICLY_MAX_STREAMS_FRAME_CAPACITY, &sent, on_ack_max_streams)) != 0)
        return ret;
    s->dst = quicly_encode_max_streams_frame(s->dst, uni, new_count);
    sent->data.max_streams.uni = uni;
    quicly_maxsender_record(maxsender, new_count, &sent->data.max_streams.args);

    QUICLY_PROBE(MAX_STREAMS_SEND, conn, probe_now(), new_count, uni);

    return 0;
}