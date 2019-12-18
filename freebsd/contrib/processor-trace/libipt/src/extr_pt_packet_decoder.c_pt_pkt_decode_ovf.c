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
struct pt_packet_decoder {int dummy; } ;
struct pt_packet {int size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppt_ovf ; 
 int pte_internal ; 
 int ptps_ovf ; 

int pt_pkt_decode_ovf(struct pt_packet_decoder *decoder,
		      struct pt_packet *packet)
{
	(void) decoder;

	if (!packet)
		return -pte_internal;

	packet->type = ppt_ovf;
	packet->size = ptps_ovf;

	return ptps_ovf;
}