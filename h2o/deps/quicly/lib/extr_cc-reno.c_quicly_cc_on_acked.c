#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ recovery_end; scalar_t__ cwnd; scalar_t__ ssthresh; scalar_t__ stash; } ;
typedef  TYPE_1__ quicly_cc_t ;

/* Variables and functions */
 scalar_t__ QUICLY_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

void quicly_cc_on_acked(quicly_cc_t *cc, uint32_t bytes, uint64_t largest_acked, uint32_t inflight)
{
    assert(inflight >= bytes);
    // no increases while in recovery
    if (largest_acked < cc->recovery_end)
        return;

    // slow start
    if (cc->cwnd < cc->ssthresh) {
        cc->cwnd += bytes;
        return;
    }
    // congestion avoidance
    cc->stash += bytes;
    if (cc->stash < cc->cwnd)
        return;
    // increase cwnd by 1 MSS per cwnd acked
    uint32_t count = cc->stash / cc->cwnd;
    cc->stash -= count * cc->cwnd;
    cc->cwnd += count * QUICLY_MAX_PACKET_SIZE;
}