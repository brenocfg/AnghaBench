#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  constant_part; } ;
struct TYPE_10__ {int /*<<< orphan*/  constant_part; } ;
struct TYPE_9__ {int /*<<< orphan*/  constant_part; } ;
struct TYPE_12__ {int off_nl_nosnap; int /*<<< orphan*/  prevlinktype; int /*<<< orphan*/  linktype; int /*<<< orphan*/  is_atm; int /*<<< orphan*/  off_nl; TYPE_3__ off_linkhdr; TYPE_2__ off_linkpl; TYPE_1__ off_linktype; int /*<<< orphan*/  off_payload; } ;
typedef  TYPE_4__ compiler_state_t ;

/* Variables and functions */
#define  A_BCC 135 
#define  A_ILMIC 134 
#define  A_LANE 133 
#define  A_LLC 132 
#define  A_METAC 131 
#define  A_OAMF4EC 130 
#define  A_OAMF4SC 129 
 int /*<<< orphan*/  A_PROTOTYPE ; 
#define  A_SC 128 
 int /*<<< orphan*/  A_VCI ; 
 int /*<<< orphan*/  A_VPI ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int /*<<< orphan*/  DLT_EN10MB ; 
 int PT_LANE ; 
 int PT_LLC ; 
 int /*<<< orphan*/  PUSH_LINKHDR (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_atmfield_code (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct block *
gen_atmtype_abbrev(compiler_state_t *cstate, int type)
{
	struct block *b0, *b1;

	switch (type) {

	case A_METAC:
		/* Get all packets in Meta signalling Circuit */
		if (!cstate->is_atm)
			bpf_error(cstate, "'metac' supported only on raw ATM");
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 1, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_BCC:
		/* Get all packets in Broadcast Circuit*/
		if (!cstate->is_atm)
			bpf_error(cstate, "'bcc' supported only on raw ATM");
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 2, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_OAMF4SC:
		/* Get all cells in Segment OAM F4 circuit*/
		if (!cstate->is_atm)
			bpf_error(cstate, "'oam4sc' supported only on raw ATM");
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 3, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_OAMF4EC:
		/* Get all cells in End-to-End OAM F4 Circuit*/
		if (!cstate->is_atm)
			bpf_error(cstate, "'oam4ec' supported only on raw ATM");
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 4, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_SC:
		/*  Get all packets in connection Signalling Circuit */
		if (!cstate->is_atm)
			bpf_error(cstate, "'sc' supported only on raw ATM");
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 5, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_ILMIC:
		/* Get all packets in ILMI Circuit */
		if (!cstate->is_atm)
			bpf_error(cstate, "'ilmic' supported only on raw ATM");
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 16, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_LANE:
		/* Get all LANE packets */
		if (!cstate->is_atm)
			bpf_error(cstate, "'lane' supported only on raw ATM");
		b1 = gen_atmfield_code(cstate, A_PROTOTYPE, PT_LANE, BPF_JEQ, 0);

		/*
		 * Arrange that all subsequent tests assume LANE
		 * rather than LLC-encapsulated packets, and set
		 * the offsets appropriately for LANE-encapsulated
		 * Ethernet.
		 *
		 * We assume LANE means Ethernet, not Token Ring.
		 */
		PUSH_LINKHDR(cstate, DLT_EN10MB, 0,
		    cstate->off_payload + 2,	/* Ethernet header */
		    -1);
		cstate->off_linktype.constant_part = cstate->off_linkhdr.constant_part + 12;
		cstate->off_linkpl.constant_part = cstate->off_linkhdr.constant_part + 14;	/* Ethernet */
		cstate->off_nl = 0;			/* Ethernet II */
		cstate->off_nl_nosnap = 3;		/* 802.3+802.2 */
		break;

	case A_LLC:
		/* Get all LLC-encapsulated packets */
		if (!cstate->is_atm)
			bpf_error(cstate, "'llc' supported only on raw ATM");
		b1 = gen_atmfield_code(cstate, A_PROTOTYPE, PT_LLC, BPF_JEQ, 0);
		cstate->linktype = cstate->prevlinktype;
		break;

	default:
		abort();
	}
	return b1;
}