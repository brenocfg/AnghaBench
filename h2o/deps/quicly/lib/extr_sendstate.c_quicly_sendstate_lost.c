#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {TYPE_3__* ranges; } ;
struct TYPE_10__ {size_t num_ranges; TYPE_1__* ranges; } ;
struct TYPE_12__ {TYPE_8__ pending; TYPE_2__ acked; } ;
typedef  TYPE_4__ quicly_sendstate_t ;
struct TYPE_13__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_5__ quicly_sendstate_sent_t ;
struct TYPE_11__ {scalar_t__ start; } ;
struct TYPE_9__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int quicly_ranges_add (TYPE_8__*,scalar_t__,scalar_t__) ; 

int quicly_sendstate_lost(quicly_sendstate_t *state, quicly_sendstate_sent_t *args)
{
    uint64_t start = args->start, end = args->end;
    size_t acked_slot = 0;
    int ret;

    while (start < end) {
        if (start < state->acked.ranges[acked_slot].end)
            start = state->acked.ranges[acked_slot].end;
        ++acked_slot;
        if (acked_slot == state->acked.num_ranges || end <= state->acked.ranges[acked_slot].start) {
            if (!(start < end))
                return 0;
            return quicly_ranges_add(&state->pending, start, end);
        }
        if (start < state->acked.ranges[acked_slot].start) {
            if ((ret = quicly_ranges_add(&state->pending, start, state->acked.ranges[acked_slot].start)) != 0)
                return ret;
        }
    }

    assert(state->acked.ranges[0].end <= state->pending.ranges[0].start);
    return 0;
}