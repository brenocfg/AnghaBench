#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  quicly_packet_allocator_t ;
struct TYPE_5__ {int /*<<< orphan*/ * base; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ quicly_datagram_t ;

/* Variables and functions */
 TYPE_2__* malloc (int) ; 

__attribute__((used)) static quicly_datagram_t *default_alloc_packet(quicly_packet_allocator_t *self, size_t payloadsize)
{
    quicly_datagram_t *packet;

    if ((packet = malloc(sizeof(*packet) + payloadsize)) == NULL)
        return NULL;
    packet->data.base = (uint8_t *)packet + sizeof(*packet);

    return packet;
}