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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ largest_acknowledged; scalar_t__ ack_delay; scalar_t__ smallest_acknowledged; scalar_t__ num_gaps; scalar_t__* ack_block_lengths; scalar_t__* gaps; } ;
typedef  TYPE_1__ quicly_ack_frame_t ;

/* Variables and functions */
 scalar_t__ QUICLY_ACK_MAX_GAPS ; 
 int QUICLY_TRANSPORT_ERROR_FRAME_ENCODING ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ quicly_decodev (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 

int quicly_decode_ack_frame(const uint8_t **src, const uint8_t *end, quicly_ack_frame_t *frame, int is_ack_ecn)
{
    uint64_t i, num_gaps, gap, ack_range;

    if ((frame->largest_acknowledged = quicly_decodev(src, end)) == UINT64_MAX)
        goto Error;
    if ((frame->ack_delay = quicly_decodev(src, end)) == UINT64_MAX)
        goto Error;
    if ((num_gaps = quicly_decodev(src, end)) == UINT64_MAX)
        goto Error;

    if ((ack_range = quicly_decodev(src, end)) == UINT64_MAX)
        goto Error;
    if (frame->largest_acknowledged < ack_range)
        goto Error;
    frame->smallest_acknowledged = frame->largest_acknowledged - ack_range;
    frame->ack_block_lengths[0] = ack_range + 1;
    frame->num_gaps = 0;

    for (i = 0; i != num_gaps; ++i) {
        if ((gap = quicly_decodev(src, end)) == UINT64_MAX)
            goto Error;
        if ((ack_range = quicly_decodev(src, end)) == UINT64_MAX)
            goto Error;
        if (i < QUICLY_ACK_MAX_GAPS) {
            if (frame->smallest_acknowledged < gap + ack_range + 2)
                goto Error;
            frame->gaps[i] = gap + 1;
            frame->ack_block_lengths[i + 1] = ack_range + 1;
            frame->smallest_acknowledged -= gap + ack_range + 2;
            ++frame->num_gaps;
        }
    }

    if (is_ack_ecn) {
        /* just skip ECT(0), ECT(1), ECT-CE counters for the time being */
        for (i = 0; i != 3; ++i)
            if (quicly_decodev(src, end) == UINT64_MAX)
                goto Error;
    }
    return 0;
Error:
    return QUICLY_TRANSPORT_ERROR_FRAME_ENCODING;
}