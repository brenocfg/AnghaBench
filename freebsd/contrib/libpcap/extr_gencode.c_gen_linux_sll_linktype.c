#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  constant_part; } ;
struct TYPE_7__ {TYPE_1__ off_linkpl; } ;
typedef  TYPE_2__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_H ; 
 int ETHERMTU ; 
#define  ETHERTYPE_AARP 133 
#define  ETHERTYPE_ATALK 132 
 int const ETHERTYPE_IPX ; 
 int /*<<< orphan*/  LINUX_SLL_P_802_2 ; 
 int /*<<< orphan*/  LINUX_SLL_P_802_3 ; 
#define  LLCSAP_IP 131 
#define  LLCSAP_IPX 130 
#define  LLCSAP_ISONS 129 
#define  LLCSAP_NETBEUI 128 
 int /*<<< orphan*/  OR_LINKHDR ; 
 int /*<<< orphan*/  OR_LINKTYPE ; 
 int /*<<< orphan*/  OR_LLC ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_cmp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_snap (TYPE_2__*,int,int const) ; 

__attribute__((used)) static struct block *
gen_linux_sll_linktype(compiler_state_t *cstate, int proto)
{
	struct block *b0, *b1;

	switch (proto) {

	case LLCSAP_ISONS:
	case LLCSAP_IP:
	case LLCSAP_NETBEUI:
		/*
		 * OSI protocols and NetBEUI always use 802.2 encapsulation,
		 * so we check the DSAP and SSAP.
		 *
		 * LLCSAP_IP checks for IP-over-802.2, rather
		 * than IP-over-Ethernet or IP-over-SNAP.
		 *
		 * XXX - should we check both the DSAP and the
		 * SSAP, like this, or should we check just the
		 * DSAP, as we do for other types <= ETHERMTU
		 * (i.e., other SAP values)?
		 */
		b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, LINUX_SLL_P_802_2);
		b1 = gen_cmp(cstate, OR_LLC, 0, BPF_H, (bpf_int32)
			     ((proto << 8) | proto));
		gen_and(b0, b1);
		return b1;

	case LLCSAP_IPX:
		/*
		 *	Ethernet_II frames, which are Ethernet
		 *	frames with a frame type of ETHERTYPE_IPX;
		 *
		 *	Ethernet_802.3 frames, which have a frame
		 *	type of LINUX_SLL_P_802_3;
		 *
		 *	Ethernet_802.2 frames, which are 802.3
		 *	frames with an 802.2 LLC header (i.e, have
		 *	a frame type of LINUX_SLL_P_802_2) and
		 *	with the IPX LSAP as the DSAP in the LLC
		 *	header;
		 *
		 *	Ethernet_SNAP frames, which are 802.3
		 *	frames with an LLC header and a SNAP
		 *	header and with an OUI of 0x000000
		 *	(encapsulated Ethernet) and a protocol
		 *	ID of ETHERTYPE_IPX in the SNAP header.
		 *
		 * First, do the checks on LINUX_SLL_P_802_2
		 * frames; generate the check for either
		 * Ethernet_802.2 or Ethernet_SNAP frames, and
		 * then put a check for LINUX_SLL_P_802_2 frames
		 * before it.
		 */
		b0 = gen_cmp(cstate, OR_LLC, 0, BPF_B, (bpf_int32)LLCSAP_IPX);
		b1 = gen_snap(cstate, 0x000000, ETHERTYPE_IPX);
		gen_or(b0, b1);
		b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, LINUX_SLL_P_802_2);
		gen_and(b0, b1);

		/*
		 * Now check for 802.3 frames and OR that with
		 * the previous test.
		 */
		b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, LINUX_SLL_P_802_3);
		gen_or(b0, b1);

		/*
		 * Now add the check for Ethernet_II frames, and
		 * do that before checking for the other frame
		 * types.
		 */
		b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, (bpf_int32)ETHERTYPE_IPX);
		gen_or(b0, b1);
		return b1;

	case ETHERTYPE_ATALK:
	case ETHERTYPE_AARP:
		/*
		 * EtherTalk (AppleTalk protocols on Ethernet link
		 * layer) may use 802.2 encapsulation.
		 */

		/*
		 * Check for 802.2 encapsulation (EtherTalk phase 2?);
		 * we check for the 802.2 protocol type in the
		 * "Ethernet type" field.
		 */
		b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, LINUX_SLL_P_802_2);

		/*
		 * 802.2-encapsulated ETHERTYPE_ATALK packets are
		 * SNAP packets with an organization code of
		 * 0x080007 (Apple, for Appletalk) and a protocol
		 * type of ETHERTYPE_ATALK (Appletalk).
		 *
		 * 802.2-encapsulated ETHERTYPE_AARP packets are
		 * SNAP packets with an organization code of
		 * 0x000000 (encapsulated Ethernet) and a protocol
		 * type of ETHERTYPE_AARP (Appletalk ARP).
		 */
		if (proto == ETHERTYPE_ATALK)
			b1 = gen_snap(cstate, 0x080007, ETHERTYPE_ATALK);
		else	/* proto == ETHERTYPE_AARP */
			b1 = gen_snap(cstate, 0x000000, ETHERTYPE_AARP);
		gen_and(b0, b1);

		/*
		 * Check for Ethernet encapsulation (Ethertalk
		 * phase 1?); we just check for the Ethernet
		 * protocol type.
		 */
		b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, (bpf_int32)proto);

		gen_or(b0, b1);
		return b1;

	default:
		if (proto <= ETHERMTU) {
			/*
			 * This is an LLC SAP value, so the frames
			 * that match would be 802.2 frames.
			 * Check for the 802.2 protocol type
			 * in the "Ethernet type" field, and
			 * then check the DSAP.
			 */
			b0 = gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, LINUX_SLL_P_802_2);
			b1 = gen_cmp(cstate, OR_LINKHDR, cstate->off_linkpl.constant_part, BPF_B,
			     (bpf_int32)proto);
			gen_and(b0, b1);
			return b1;
		} else {
			/*
			 * This is an Ethernet type, so compare
			 * the length/type field with it (if
			 * the frame is an 802.2 frame, the length
			 * field will be <= ETHERMTU, and, as
			 * "proto" is > ETHERMTU, this test
			 * will fail and the frame won't match,
			 * which is what we want).
			 */
			return gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H, (bpf_int32)proto);
		}
	}
}