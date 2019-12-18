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
typedef  int /*<<< orphan*/  uint8_t ;
struct pt_packet_decoder {int /*<<< orphan*/  config; int /*<<< orphan*/  pos; } ;
struct pt_packet {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppt_psb ; 
 int pt_pkt_read_psb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pte_internal ; 

int pt_pkt_decode_psb(struct pt_packet_decoder *decoder,
		      struct pt_packet *packet)
{
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_psb(decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	packet->type = ppt_psb;
	packet->size = (uint8_t) size;

	return size;
}