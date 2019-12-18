#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int num_ranges; TYPE_1__* ranges; } ;
struct TYPE_6__ {scalar_t__ final_size; int /*<<< orphan*/  size_inflight; TYPE_4__ pending; } ;
typedef  TYPE_2__ quicly_sendstate_t ;
struct TYPE_5__ {scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 int quicly_ranges_add (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 

int quicly_sendstate_activate(quicly_sendstate_t *state)
{
    uint64_t end_off = state->final_size;

    /* take EOS position into account */
    if (end_off != UINT64_MAX)
        ++end_off;

    /* do nothing if already active */
    if (state->pending.num_ranges != 0 && state->pending.ranges[state->pending.num_ranges - 1].end == end_off)
        return 0;

    return quicly_ranges_add(&state->pending, state->size_inflight, end_off);
}