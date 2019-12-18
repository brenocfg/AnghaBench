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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ recovery_end; int cwnd; int ssthresh; } ;
typedef  TYPE_1__ quicly_cc_t ;

/* Variables and functions */
 int QUICLY_MAX_PACKET_SIZE ; 
 int QUICLY_MIN_CWND ; 
 int QUICLY_RENO_BETA ; 

void quicly_cc_on_lost(quicly_cc_t *cc, uint32_t bytes, uint64_t lost_pn, uint64_t next_pn)
{
    // nothing to do if loss is in recovery window
    if (lost_pn < cc->recovery_end)
        return;
    // set end of recovery window
    cc->recovery_end = next_pn;
    cc->cwnd *= QUICLY_RENO_BETA;
    if (cc->cwnd < QUICLY_MIN_CWND * QUICLY_MAX_PACKET_SIZE)
        cc->cwnd = QUICLY_MIN_CWND * QUICLY_MAX_PACKET_SIZE;
    cc->ssthresh = cc->cwnd;
}