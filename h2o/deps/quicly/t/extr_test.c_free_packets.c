#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_datagram_t ;
struct TYPE_4__ {TYPE_1__* packet_allocator; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_packet ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__ quic_ctx ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void free_packets(quicly_datagram_t **packets, size_t cnt)
{
    size_t i;
    for (i = 0; i != cnt; ++i)
        quic_ctx.packet_allocator->free_packet(quic_ctx.packet_allocator, packets[i]);
}