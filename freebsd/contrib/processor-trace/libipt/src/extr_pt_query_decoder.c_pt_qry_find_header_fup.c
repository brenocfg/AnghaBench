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
struct pt_packet {int type; } ;

/* Variables and functions */
#define  ppt_fup 129 
#define  ppt_psbend 128 
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_qry_find_header_fup(struct pt_packet *packet,
				  struct pt_packet_decoder *decoder)
{
	if (!packet || !decoder)
		return -pte_internal;

	for (;;) {
		int errcode;

		errcode = pt_pkt_next(decoder, packet, sizeof(*packet));
		if (errcode < 0)
			return errcode;

		switch (packet->type) {
		default:
			/* Ignore the packet. */
			break;

		case ppt_psbend:
			/* There's no FUP in here. */
			return 0;

		case ppt_fup:
			/* Found it. */
			return 1;
		}
	}
}