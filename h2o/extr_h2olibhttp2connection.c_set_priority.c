#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  node; } ;
struct TYPE_19__ {TYPE_10__ _scheduler; } ;
typedef  TYPE_4__ h2o_http2_stream_t ;
typedef  int /*<<< orphan*/  h2o_http2_scheduler_node_t ;
struct TYPE_20__ {scalar_t__ dependency; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  weight; } ;
typedef  TYPE_5__ h2o_http2_priority_t ;
struct TYPE_18__ {TYPE_2__** streams; } ;
struct TYPE_21__ {int /*<<< orphan*/  scheduler; TYPE_3__ _recently_closed_streams; } ;
typedef  TYPE_6__ h2o_http2_conn_t ;
struct TYPE_16__ {int /*<<< orphan*/  node; } ;
struct TYPE_17__ {scalar_t__ stream_id; TYPE_1__ _scheduler; } ;

/* Variables and functions */
 size_t HTTP2_CLOSED_STREAM_PRIORITIES ; 
 TYPE_4__* h2o_http2_conn_get_stream (TYPE_6__*,scalar_t__) ; 
 TYPE_5__ h2o_http2_default_priority ; 
 int /*<<< orphan*/  h2o_http2_scheduler_open (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_rebind (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_priority(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream, const h2o_http2_priority_t *priority,
                         int scheduler_is_open)
{
    h2o_http2_scheduler_node_t *parent_sched = NULL;

    /* determine the parent */
    if (priority->dependency != 0) {
        h2o_http2_stream_t *parent_stream = h2o_http2_conn_get_stream(conn, priority->dependency);
        if (parent_stream != NULL) {
            parent_sched = &parent_stream->_scheduler.node;
        } else {
            size_t i;
            for (i = 0; i < HTTP2_CLOSED_STREAM_PRIORITIES; i++) {
                if (conn->_recently_closed_streams.streams[i] &&
                    conn->_recently_closed_streams.streams[i]->stream_id == priority->dependency) {
                    parent_sched = &conn->_recently_closed_streams.streams[i]->_scheduler.node;
                    break;
                }
            }
            if (parent_sched == NULL) {
                /* A dependency on a stream that is not currently in the tree - such as a stream in the "idle" state - results in
                 * that stream being given a default priority. (RFC 7540 5.3.1) It is possible for a stream to become closed while
                 * prioritization information that creates a dependency on that stream is in transit. If a stream identified in a
                 * dependency has no associated priority information, then the dependent stream is instead assigned a default
                 * priority. (RFC 7540 5.3.4)
                 */
                parent_sched = &conn->scheduler;
                priority = &h2o_http2_default_priority;
            }
        }
    } else {
        parent_sched = &conn->scheduler;
    }

    /* setup the scheduler */
    if (!scheduler_is_open) {
        h2o_http2_scheduler_open(&stream->_scheduler, parent_sched, priority->weight, priority->exclusive);
    } else {
        h2o_http2_scheduler_rebind(&stream->_scheduler, parent_sched, priority->weight, priority->exclusive);
    }
}