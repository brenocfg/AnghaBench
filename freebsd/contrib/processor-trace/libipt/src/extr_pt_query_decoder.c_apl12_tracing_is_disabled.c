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
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
#define  ppt_invalid 138 
#define  ppt_ovf 137 
#define  ppt_psb 136 
#define  ppt_psbend 135 
#define  ppt_stop 134 
#define  ppt_tip 133 
#define  ppt_tip_pgd 132 
#define  ppt_tip_pge 131 
#define  ppt_tnt_64 130 
#define  ppt_tnt_8 129 
#define  ppt_unknown 128 
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int pt_qry_find_header_fup (struct pt_packet*,struct pt_packet_decoder*) ; 
 int pte_bad_context ; 
 int pte_eos ; 
 int pte_internal ; 

__attribute__((used)) static int apl12_tracing_is_disabled(struct pt_packet_decoder *decoder)
{
	if (!decoder)
		return -pte_internal;

	for (;;) {
		struct pt_packet packet;
		int status;

		status = pt_pkt_next(decoder, &packet, sizeof(packet));
		if (status < 0) {
			/* Running out of packets is not an error. */
			if (status == -pte_eos)
				status = 1;

			return status;
		}

		switch (packet.type) {
		default:
			/* Skip other packets. */
			break;

		case ppt_stop:
			/* Tracing is disabled before a stop. */
			return 0;

		case ppt_tip_pge:
			/* Tracing gets enabled - it must have been disabled. */
			return 0;

		case ppt_tnt_8:
		case ppt_tnt_64:
		case ppt_tip:
		case ppt_tip_pgd:
			/* Those packets are only generated when tracing is
			 * enabled.  We're done.
			 */
			return 1;

		case ppt_psb:
			/* We reached a synchronization point.  Tracing is
			 * enabled if and only if the PSB+ contains a FUP.
			 */
			status = pt_qry_find_header_fup(&packet, decoder);

			/* If we ran out of packets, we can't tell. */
			if (status == -pte_eos)
				status = 1;

			return status;

		case ppt_psbend:
			/* We shouldn't see this. */
			return -pte_bad_context;

		case ppt_ovf:
			/* It doesn't matter - we run into the next overflow. */
			return 1;

		case ppt_unknown:
		case ppt_invalid:
			/* We can't skip this packet. */
			return 1;
		}
	}
}