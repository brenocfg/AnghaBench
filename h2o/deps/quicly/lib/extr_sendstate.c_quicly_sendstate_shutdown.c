#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int num_ranges; TYPE_1__* ranges; } ;
struct TYPE_7__ {scalar_t__ size_inflight; scalar_t__ final_size; TYPE_5__ pending; } ;
typedef  TYPE_2__ quicly_sendstate_t ;
struct TYPE_6__ {scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int quicly_ranges_add (TYPE_5__*,scalar_t__,scalar_t__) ; 
 int quicly_sendstate_is_open (TYPE_2__*) ; 

int quicly_sendstate_shutdown(quicly_sendstate_t *state, uint64_t final_size)
{
    int ret;

    assert(quicly_sendstate_is_open(state));
    assert(state->size_inflight <= final_size);

    if (state->pending.num_ranges != 0 && state->pending.ranges[state->pending.num_ranges - 1].end == UINT64_MAX) {
        state->pending.ranges[state->pending.num_ranges - 1].end = final_size + 1;
    } else {
        if ((ret = quicly_ranges_add(&state->pending, state->size_inflight, final_size + 1)) != 0)
            return ret;
    }

    state->final_size = final_size;
    return 0;
}