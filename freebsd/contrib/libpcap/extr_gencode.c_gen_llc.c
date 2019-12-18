#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_9__ {int linktype; } ;
typedef  TYPE_1__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  A_LLC ; 
 int /*<<< orphan*/  BPF_H ; 
#define  DLT_ATM_RFC1483 137 
#define  DLT_EN10MB 136 
#define  DLT_FDDI 135 
#define  DLT_IEEE802 134 
#define  DLT_IEEE802_11 133 
#define  DLT_IEEE802_11_RADIO 132 
#define  DLT_IEEE802_11_RADIO_AVS 131 
#define  DLT_PPI 130 
#define  DLT_PRISM_HEADER 129 
#define  DLT_SUNATM 128 
 int /*<<< orphan*/  ETHERMTU ; 
 int /*<<< orphan*/  OR_LINKTYPE ; 
 int /*<<< orphan*/  OR_LLC ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_atmtype_abbrev (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct block* gen_check_802_11_data_frame (TYPE_1__*) ; 
 struct block* gen_cmp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_cmp_gt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 struct block* gen_true (TYPE_1__*) ; 

struct block *
gen_llc(compiler_state_t *cstate)
{
	struct block *b0, *b1;

	switch (cstate->linktype) {

	case DLT_EN10MB:
		/*
		 * We check for an Ethernet type field less than
		 * 1500, which means it's an 802.3 length field.
		 */
		b0 = gen_cmp_gt(cstate, OR_LINKTYPE, 0, BPF_H, ETHERMTU);
		gen_not(b0);

		/*
		 * Now check for the purported DSAP and SSAP not being
		 * 0xFF, to rule out NetWare-over-802.3.
		 */
		b1 = gen_cmp(cstate, OR_LLC, 0, BPF_H, (bpf_int32)0xFFFF);
		gen_not(b1);
		gen_and(b0, b1);
		return b1;

	case DLT_SUNATM:
		/*
		 * We check for LLC traffic.
		 */
		b0 = gen_atmtype_abbrev(cstate, A_LLC);
		return b0;

	case DLT_IEEE802:	/* Token Ring */
		/*
		 * XXX - check for LLC frames.
		 */
		return gen_true(cstate);

	case DLT_FDDI:
		/*
		 * XXX - check for LLC frames.
		 */
		return gen_true(cstate);

	case DLT_ATM_RFC1483:
		/*
		 * For LLC encapsulation, these are defined to have an
		 * 802.2 LLC header.
		 *
		 * For VC encapsulation, they don't, but there's no
		 * way to check for that; the protocol used on the VC
		 * is negotiated out of band.
		 */
		return gen_true(cstate);

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_PPI:
		/*
		 * Check that we have a data frame.
		 */
		b0 = gen_check_802_11_data_frame(cstate);
		return b0;

	default:
		bpf_error(cstate, "'llc' not supported for linktype %d", cstate->linktype);
		/* NOTREACHED */
	}
}