#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  off_li_hsl; int /*<<< orphan*/  linktype; int /*<<< orphan*/  off_li; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_H ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int /*<<< orphan*/  BPF_JGT ; 
 int /*<<< orphan*/  DLT_ERF ; 
 int /*<<< orphan*/  DLT_MTP2 ; 
 int /*<<< orphan*/  DLT_MTP2_WITH_PHDR ; 
#define  MH_FISU 133 
#define  MH_LSSU 132 
#define  MH_MSU 131 
#define  M_FISU 130 
#define  M_LSSU 129 
#define  M_MSU 128 
 int /*<<< orphan*/  OR_PACKET ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_ncmp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

struct block *
gen_mtp2type_abbrev(compiler_state_t *cstate, int type)
{
	struct block *b0, *b1;

	switch (type) {

	case M_FISU:
		if ( (cstate->linktype != DLT_MTP2) &&
		     (cstate->linktype != DLT_ERF) &&
		     (cstate->linktype != DLT_MTP2_WITH_PHDR) )
			bpf_error(cstate, "'fisu' supported only on MTP2");
		/* gen_ncmp(cstate, offrel, offset, size, mask, jtype, reverse, value) */
		b0 = gen_ncmp(cstate, OR_PACKET, cstate->off_li, BPF_B, 0x3f, BPF_JEQ, 0, 0);
		break;

	case M_LSSU:
		if ( (cstate->linktype != DLT_MTP2) &&
		     (cstate->linktype != DLT_ERF) &&
		     (cstate->linktype != DLT_MTP2_WITH_PHDR) )
			bpf_error(cstate, "'lssu' supported only on MTP2");
		b0 = gen_ncmp(cstate, OR_PACKET, cstate->off_li, BPF_B, 0x3f, BPF_JGT, 1, 2);
		b1 = gen_ncmp(cstate, OR_PACKET, cstate->off_li, BPF_B, 0x3f, BPF_JGT, 0, 0);
		gen_and(b1, b0);
		break;

	case M_MSU:
		if ( (cstate->linktype != DLT_MTP2) &&
		     (cstate->linktype != DLT_ERF) &&
		     (cstate->linktype != DLT_MTP2_WITH_PHDR) )
			bpf_error(cstate, "'msu' supported only on MTP2");
		b0 = gen_ncmp(cstate, OR_PACKET, cstate->off_li, BPF_B, 0x3f, BPF_JGT, 0, 2);
		break;

	case MH_FISU:
		if ( (cstate->linktype != DLT_MTP2) &&
		     (cstate->linktype != DLT_ERF) &&
		     (cstate->linktype != DLT_MTP2_WITH_PHDR) )
			bpf_error(cstate, "'hfisu' supported only on MTP2_HSL");
		/* gen_ncmp(cstate, offrel, offset, size, mask, jtype, reverse, value) */
		b0 = gen_ncmp(cstate, OR_PACKET, cstate->off_li_hsl, BPF_H, 0xff80, BPF_JEQ, 0, 0);
		break;

	case MH_LSSU:
		if ( (cstate->linktype != DLT_MTP2) &&
		     (cstate->linktype != DLT_ERF) &&
		     (cstate->linktype != DLT_MTP2_WITH_PHDR) )
			bpf_error(cstate, "'hlssu' supported only on MTP2_HSL");
		b0 = gen_ncmp(cstate, OR_PACKET, cstate->off_li_hsl, BPF_H, 0xff80, BPF_JGT, 1, 0x0100);
		b1 = gen_ncmp(cstate, OR_PACKET, cstate->off_li_hsl, BPF_H, 0xff80, BPF_JGT, 0, 0);
		gen_and(b1, b0);
		break;

	case MH_MSU:
		if ( (cstate->linktype != DLT_MTP2) &&
		     (cstate->linktype != DLT_ERF) &&
		     (cstate->linktype != DLT_MTP2_WITH_PHDR) )
			bpf_error(cstate, "'hmsu' supported only on MTP2_HSL");
		b0 = gen_ncmp(cstate, OR_PACKET, cstate->off_li_hsl, BPF_H, 0xff80, BPF_JGT, 0, 0x0100);
		break;

	default:
		abort();
	}
	return b0;
}