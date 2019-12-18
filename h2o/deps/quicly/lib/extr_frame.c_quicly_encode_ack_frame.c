#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_5__ {int num_ranges; TYPE_1__* ranges; } ;
typedef  TYPE_2__ quicly_ranges_t ;
struct TYPE_4__ {int end; int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_FRAME_TYPE_ACK ; 
 int /*<<< orphan*/  WRITE_BLOCK (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * quicly_encodev (int /*<<< orphan*/ *,int) ; 

uint8_t *quicly_encode_ack_frame(uint8_t *dst, uint8_t *dst_end, quicly_ranges_t *ranges, uint64_t ack_delay)
{
#define WRITE_BLOCK(start, end)                                                                                                    \
    do {                                                                                                                           \
        uint64_t _start = (start), _end = (end);                                                                                   \
        assert(_start < _end);                                                                                                     \
        if (dst_end - dst < 8)                                                                                                     \
            return NULL;                                                                                                           \
        dst = quicly_encodev(dst, _end - _start - 1);                                                                              \
    } while (0)

    size_t range_index = ranges->num_ranges - 1;

    assert(ranges->num_ranges != 0);

    *dst++ = QUICLY_FRAME_TYPE_ACK;
    dst = quicly_encodev(dst, ranges->ranges[range_index].end - 1); /* largest acknowledged */
    dst = quicly_encodev(dst, ack_delay);                           /* ack delay */
    dst = quicly_encodev(dst, ranges->num_ranges - 1);              /* ack blocks */

    while (1) {
        WRITE_BLOCK(ranges->ranges[range_index].start, ranges->ranges[range_index].end); /* ACK block count */
        if (range_index-- == 0)
            break;
        WRITE_BLOCK(ranges->ranges[range_index].end, ranges->ranges[range_index + 1].start);
    }

    return dst;

#undef WRITE_BLOCK
}