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
struct pt_decoder_function {int dummy; } ;
struct pt_config {int* begin; int* end; } ;

/* Variables and functions */
 struct pt_decoder_function pt_decode_cbr ; 
 struct pt_decoder_function pt_decode_cyc ; 
 struct pt_decoder_function pt_decode_exstop ; 
 struct pt_decoder_function pt_decode_fup ; 
 struct pt_decoder_function pt_decode_mnt ; 
 struct pt_decoder_function pt_decode_mode ; 
 struct pt_decoder_function pt_decode_mtc ; 
 struct pt_decoder_function pt_decode_mwait ; 
 struct pt_decoder_function pt_decode_ovf ; 
 struct pt_decoder_function pt_decode_pad ; 
 struct pt_decoder_function pt_decode_pip ; 
 struct pt_decoder_function pt_decode_psb ; 
 struct pt_decoder_function pt_decode_psbend ; 
 struct pt_decoder_function pt_decode_ptw ; 
 struct pt_decoder_function pt_decode_pwre ; 
 struct pt_decoder_function pt_decode_pwrx ; 
 struct pt_decoder_function pt_decode_stop ; 
 struct pt_decoder_function pt_decode_tip ; 
 struct pt_decoder_function pt_decode_tip_pgd ; 
 struct pt_decoder_function pt_decode_tip_pge ; 
 struct pt_decoder_function pt_decode_tma ; 
 struct pt_decoder_function pt_decode_tnt_64 ; 
 struct pt_decoder_function pt_decode_tnt_8 ; 
 struct pt_decoder_function pt_decode_tsc ; 
 struct pt_decoder_function pt_decode_unknown ; 
 struct pt_decoder_function pt_decode_vmcs ; 
#define  pt_ext2_mnt 148 
#define  pt_ext_cbr 147 
#define  pt_ext_exstop 146 
#define  pt_ext_exstop_ip 145 
#define  pt_ext_ext2 144 
#define  pt_ext_mwait 143 
#define  pt_ext_ovf 142 
#define  pt_ext_pip 141 
#define  pt_ext_psb 140 
#define  pt_ext_psbend 139 
 int pt_ext_ptw ; 
#define  pt_ext_pwre 138 
#define  pt_ext_pwrx 137 
#define  pt_ext_stop 136 
#define  pt_ext_tma 135 
#define  pt_ext_tnt_64 134 
#define  pt_ext_vmcs 133 
 int pt_opc_cyc ; 
#define  pt_opc_ext 132 
 int pt_opc_fup ; 
#define  pt_opc_mode 131 
#define  pt_opc_mtc 130 
#define  pt_opc_pad 129 
 int pt_opc_tip ; 
 int pt_opc_tip_pgd ; 
 int pt_opc_tip_pge ; 
 int pt_opc_tnt_8 ; 
#define  pt_opc_tsc 128 
 int pt_opm_cyc ; 
 int pt_opm_fup ; 
 int pt_opm_ptw ; 
 int pt_opm_tip ; 
 int pt_opm_tnt_8 ; 
 int pte_eos ; 
 int pte_internal ; 
 int pte_nosync ; 

int pt_df_fetch(const struct pt_decoder_function **dfun, const uint8_t *pos,
		const struct pt_config *config)
{
	const uint8_t *begin, *end;
	uint8_t opc, ext, ext2;

	if (!dfun || !config)
		return -pte_internal;

	/* Clear the decode function in case of errors. */
	*dfun = NULL;

	begin = config->begin;
	end = config->end;

	if (!pos || (pos < begin) || (end < pos))
		return -pte_nosync;

	if (pos == end)
		return -pte_eos;

	opc = *pos++;
	switch (opc) {
	default:
		/* Check opcodes that require masking. */
		if ((opc & pt_opm_tnt_8) == pt_opc_tnt_8) {
			*dfun = &pt_decode_tnt_8;
			return 0;
		}

		if ((opc & pt_opm_cyc) == pt_opc_cyc) {
			*dfun = &pt_decode_cyc;
			return 0;
		}

		if ((opc & pt_opm_tip) == pt_opc_tip) {
			*dfun = &pt_decode_tip;
			return 0;
		}

		if ((opc & pt_opm_fup) == pt_opc_fup) {
			*dfun = &pt_decode_fup;
			return 0;
		}

		if ((opc & pt_opm_tip) == pt_opc_tip_pge) {
			*dfun = &pt_decode_tip_pge;
			return 0;
		}

		if ((opc & pt_opm_tip) == pt_opc_tip_pgd) {
			*dfun = &pt_decode_tip_pgd;
			return 0;
		}

		*dfun = &pt_decode_unknown;
		return 0;

	case pt_opc_pad:
		*dfun = &pt_decode_pad;
		return 0;

	case pt_opc_mode:
		*dfun = &pt_decode_mode;
		return 0;

	case pt_opc_tsc:
		*dfun = &pt_decode_tsc;
		return 0;

	case pt_opc_mtc:
		*dfun = &pt_decode_mtc;
		return 0;

	case pt_opc_ext:
		if (pos == end)
			return -pte_eos;

		ext = *pos++;
		switch (ext) {
		default:
			/* Check opcodes that require masking. */
			if ((ext & pt_opm_ptw) == pt_ext_ptw) {
				*dfun = &pt_decode_ptw;
				return 0;
			}

			*dfun = &pt_decode_unknown;
			return 0;

		case pt_ext_psb:
			*dfun = &pt_decode_psb;
			return 0;

		case pt_ext_ovf:
			*dfun = &pt_decode_ovf;
			return 0;

		case pt_ext_tnt_64:
			*dfun = &pt_decode_tnt_64;
			return 0;

		case pt_ext_psbend:
			*dfun = &pt_decode_psbend;
			return 0;

		case pt_ext_cbr:
			*dfun = &pt_decode_cbr;
			return 0;

		case pt_ext_pip:
			*dfun = &pt_decode_pip;
			return 0;

		case pt_ext_tma:
			*dfun = &pt_decode_tma;
			return 0;

		case pt_ext_stop:
			*dfun = &pt_decode_stop;
			return 0;

		case pt_ext_vmcs:
			*dfun = &pt_decode_vmcs;
			return 0;

		case pt_ext_exstop:
		case pt_ext_exstop_ip:
			*dfun = &pt_decode_exstop;
			return 0;

		case pt_ext_mwait:
			*dfun = &pt_decode_mwait;
			return 0;

		case pt_ext_pwre:
			*dfun = &pt_decode_pwre;
			return 0;

		case pt_ext_pwrx:
			*dfun = &pt_decode_pwrx;
			return 0;

		case pt_ext_ext2:
			if (pos == end)
				return -pte_eos;

			ext2 = *pos++;
			switch (ext2) {
			default:
				*dfun = &pt_decode_unknown;
				return 0;

			case pt_ext2_mnt:
				*dfun = &pt_decode_mnt;
				return 0;
			}
		}
	}
}