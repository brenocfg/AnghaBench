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
typedef  unsigned long long uint8_t ;
typedef  unsigned long long uint64_t ;
struct pt_packet_tnt {unsigned long long payload; unsigned long long bit_size; } ;

/* Variables and functions */
 unsigned long long pt_pkt_tnt_bit_size (unsigned long long) ; 
 int pte_bad_packet ; 
 int pte_internal ; 

__attribute__((used)) static int pt_pkt_read_tnt(struct pt_packet_tnt *packet, uint64_t payload)
{
	uint8_t bit_size;

	if (!packet)
		return -pte_internal;

	bit_size = pt_pkt_tnt_bit_size(payload);
	if (!bit_size)
		return -pte_bad_packet;

	/* Remove the stop bit from the payload. */
	payload &= ~(1ull << bit_size);

	packet->payload = payload;
	packet->bit_size = bit_size;

	return 0;
}