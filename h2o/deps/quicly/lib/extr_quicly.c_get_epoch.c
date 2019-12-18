#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
 int QUICLY_EPOCH_0RTT ; 
 int QUICLY_EPOCH_1RTT ; 
 int QUICLY_EPOCH_HANDSHAKE ; 
 int QUICLY_EPOCH_INITIAL ; 
 int /*<<< orphan*/  QUICLY_PACKET_IS_LONG_HEADER (int) ; 
#define  QUICLY_PACKET_TYPE_0RTT 130 
 int QUICLY_PACKET_TYPE_BITMASK ; 
#define  QUICLY_PACKET_TYPE_HANDSHAKE 129 
#define  QUICLY_PACKET_TYPE_INITIAL 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline uint8_t get_epoch(uint8_t first_byte)
{
    if (!QUICLY_PACKET_IS_LONG_HEADER(first_byte))
        return QUICLY_EPOCH_1RTT;

    switch (first_byte & QUICLY_PACKET_TYPE_BITMASK) {
    case QUICLY_PACKET_TYPE_INITIAL:
        return QUICLY_EPOCH_INITIAL;
    case QUICLY_PACKET_TYPE_HANDSHAKE:
        return QUICLY_EPOCH_HANDSHAKE;
    case QUICLY_PACKET_TYPE_0RTT:
        return QUICLY_EPOCH_0RTT;
    default:
        assert(!"FIXME");
    }
}