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
#define  ppt_cbr 154 
#define  ppt_cyc 153 
#define  ppt_exstop 152 
#define  ppt_fup 151 
#define  ppt_invalid 150 
#define  ppt_mnt 149 
#define  ppt_mode 148 
#define  ppt_mtc 147 
#define  ppt_mwait 146 
#define  ppt_ovf 145 
#define  ppt_pad 144 
#define  ppt_pip 143 
#define  ppt_psb 142 
#define  ppt_psbend 141 
#define  ppt_ptw 140 
#define  ppt_pwre 139 
#define  ppt_pwrx 138 
#define  ppt_stop 137 
#define  ppt_tip 136 
#define  ppt_tip_pgd 135 
#define  ppt_tip_pge 134 
#define  ppt_tma 133 
#define  ppt_tnt_64 132 
#define  ppt_tnt_8 131 
#define  ppt_tsc 130 
#define  ppt_unknown 129 
#define  ppt_vmcs 128 
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int pte_bad_context ; 
 int pte_bad_opc ; 

__attribute__((used)) static int pt_pkt_find_ovf_fup(struct pt_packet_decoder *decoder)
{
	for (;;) {
		struct pt_packet packet;
		int errcode;

		errcode = pt_pkt_next(decoder, &packet, sizeof(packet));
		if (errcode < 0)
			return errcode;

		switch (packet.type) {
		case ppt_fup:
			return 1;

		case ppt_invalid:
			return -pte_bad_opc;

		case ppt_unknown:
		case ppt_pad:
		case ppt_mnt:
		case ppt_cbr:
		case ppt_tsc:
		case ppt_tma:
		case ppt_mtc:
		case ppt_cyc:
			continue;

		case ppt_psb:
		case ppt_tip_pge:
		case ppt_mode:
		case ppt_pip:
		case ppt_vmcs:
		case ppt_stop:
		case ppt_ovf:
		case ppt_exstop:
		case ppt_mwait:
		case ppt_pwre:
		case ppt_pwrx:
		case ppt_ptw:
			return 0;

		case ppt_psbend:
		case ppt_tip:
		case ppt_tip_pgd:
		case ppt_tnt_8:
		case ppt_tnt_64:
			return -pte_bad_context;
		}
	}
}