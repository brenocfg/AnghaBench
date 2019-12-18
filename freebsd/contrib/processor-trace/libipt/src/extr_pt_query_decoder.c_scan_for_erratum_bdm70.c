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
#define  ppt_cbr 139 
#define  ppt_cyc 138 
#define  ppt_mnt 137 
#define  ppt_mode 136 
#define  ppt_mtc 135 
#define  ppt_pad 134 
#define  ppt_pip 133 
#define  ppt_psbend 132 
#define  ppt_tip_pge 131 
#define  ppt_tma 130 
#define  ppt_tsc 129 
#define  ppt_vmcs 128 
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int pte_eos ; 

__attribute__((used)) static int scan_for_erratum_bdm70(struct pt_packet_decoder *decoder)
{
	for (;;) {
		struct pt_packet packet;
		int errcode;

		errcode = pt_pkt_next(decoder, &packet, sizeof(packet));
		if (errcode < 0) {
			/* Running out of packets is not an error. */
			if (errcode == -pte_eos)
				errcode = 0;

			return errcode;
		}

		switch (packet.type) {
		default:
			/* All other packets cancel our search.
			 *
			 * We do not enumerate those packets since we also
			 * want to include new packets.
			 */
			return 0;

		case ppt_tip_pge:
			/* We found it - the erratum applies. */
			return 1;

		case ppt_pad:
		case ppt_tsc:
		case ppt_cbr:
		case ppt_psbend:
		case ppt_pip:
		case ppt_mode:
		case ppt_vmcs:
		case ppt_tma:
		case ppt_mtc:
		case ppt_cyc:
		case ppt_mnt:
			/* Intentionally skip a few packets. */
			continue;
		}
	}
}