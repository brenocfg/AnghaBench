#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ num_ranges; TYPE_1__* ranges; } ;
struct TYPE_7__ {scalar_t__ const size_inflight; scalar_t__ final_size; TYPE_2__ pending; } ;
typedef  TYPE_3__ quicly_sendstate_t ;
struct TYPE_5__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int quicly_sendstate_can_send(quicly_sendstate_t *state, const uint64_t *max_stream_data)
{
    if (state->pending.num_ranges != 0) {
        /* the flow is capped either by MAX_STREAM_DATA or (in case we are hitting connection-level flow control) by the number of
         * bytes we've already sent */
        uint64_t blocked_at = max_stream_data != NULL ? *max_stream_data : state->size_inflight;
        if (state->pending.ranges[0].start < blocked_at)
            return 1;
        /* we can always send EOS, if that is the only thing to be sent */
        if (state->pending.ranges[0].start >= state->final_size) {
            assert(state->pending.ranges[0].start == state->final_size);
            return 1;
        }
    }

    return 0;
}