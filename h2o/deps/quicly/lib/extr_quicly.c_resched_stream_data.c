#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_12__ {scalar_t__ num_ranges; } ;
struct TYPE_13__ {TYPE_1__ pending; } ;
struct TYPE_18__ {int stream_id; TYPE_6__* conn; scalar_t__ streams_blocked; TYPE_2__ sendstate; } ;
typedef  TYPE_7__ quicly_stream_t ;
struct TYPE_19__ {int /*<<< orphan*/  (* update_state ) (TYPE_8__*,TYPE_7__*) ;} ;
typedef  TYPE_8__ quicly_stream_scheduler_t ;
struct TYPE_16__ {TYPE_4__* ctx; } ;
struct TYPE_14__ {int flows; } ;
struct TYPE_17__ {TYPE_5__ super; TYPE_3__ pending; } ;
struct TYPE_15__ {TYPE_8__* stream_scheduler; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,TYPE_7__*) ; 

__attribute__((used)) static void resched_stream_data(quicly_stream_t *stream)
{
    if (stream->stream_id < 0) {
        assert(-4 <= stream->stream_id);
        uint8_t mask = 1 << -(1 + stream->stream_id);
        if (stream->sendstate.pending.num_ranges != 0) {
            stream->conn->pending.flows |= mask;
        } else {
            stream->conn->pending.flows &= ~mask;
        }
        return;
    }

    /* do nothing if blocked */
    if (stream->streams_blocked)
        return;

    quicly_stream_scheduler_t *scheduler = stream->conn->super.ctx->stream_scheduler;
    scheduler->update_state(scheduler, stream);
}