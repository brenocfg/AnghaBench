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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_H ; 
 int ETHERMTU ; 
#define  ETHERTYPE_AARP 133 
#define  ETHERTYPE_ATALK 132 
 int const ETHERTYPE_IPX ; 
#define  LLCSAP_IP 131 
#define  LLCSAP_IPX 130 
#define  LLCSAP_ISONS 129 
#define  LLCSAP_NETBEUI 128 
 int /*<<< orphan*/  OR_LINKTYPE ; 
 int /*<<< orphan*/  OR_LLC ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_cmp_gt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_snap (int /*<<< orphan*/ *,int,int const) ; 

__attribute__((used)) static struct block *
gen_ether_linktype(compiler_state_t *cstate, int proto)
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
		b0 = gen_cmp_gt(cstate, OR_LINKTYPE, 0, BPF_H, ETHERMTU);
		gen_not(b0);
		b1 = gen_cmp(cstate, OR_LLC, 0, BPF_H, (bpf_int32)
			     ((proto << 8) | proto));
		gen_and(b0, b1);
		return b1;

	case LLCSAP_IPX:
		/*
		 * Check for;
		 *
		 *	Ethernet_II frames, which are Ethernet
		 *	frames with a frame type of ETHERTYPE_IPX;
		 *
		 *	Ethernet_802.3 frames, which are 802.3
		 *	frames (i.e., the type/length field is
		 *	a length field, <= ETHERMTU, rather than
		 *	a type field) with the first two bytes
		 *	after the Ethernet/802.3 header being
		 *	0xFFFF;
		 *
		 *	Ethernet_802.2 frames, which are 802.3
		 *	frames with an 802.2 LLC header and
		 *	with the IPX LSAP as the DSAP in the LLC
		 *	header;
		 *
		 *	Ethernet_SNAP frames, which are 802.3
		 *	frames with an LLC header and a SNAP
		 *	header and with an OUI of 0x000000
		 *	(encapsulated Ethernet) and a protocol
		 *	ID of ETHERTYPE_IPX in the SNAP header.
		 *
		 * XXX - should we generate the same code both
		 * for tests for LLCSAP_IPX and for ETHERTYPE_IPX?
		 */

		/*
		 * This generates code to check both for the
		 * IPX LSAP (Ethernet_802.2) and for Ethernet_802.3.
		 */
		b0 = gen_cmp(cstate, OR_LLC, 0, BPF_B, (bpf_int32)LLCSAP_IPX);
		b1 = gen_cmp(cstate, OR_LLC, 0, BPF_H, (bpf_int32)0xFFFF);
		gen_or(b0, b1);

		/*
		 * Now we add code to check for SNAP frames with
		 * ETHERTYPE_IPX, i.e. Ethernet_SNAP.
		 */
		b0 = gen_snap(cstate, 0x000000, ETHERTYPE_IPX);
		gen_or(b0, b1);

		/*
		 * Now we generate code to check for 802.3
		 * frames in general.
		 */
		b0 = gen_cmp_gt(cstate, OR_LINKTYPE, 0, BPF_H, ETHERMTU);
		gen_not(b0);

		/*
		 * Now add the check for 802.3 frames before the
		 * check for Ethernet_802.2 and Ethernet_802.3,
		 * as those checks should only be done on 802.3
		 * frames, not on Ethernet frames.
		 */
		gen_and(b0, b1);

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
		 * we check for an Ethernet type field less than
		 * 1500, which means it's an 802.3 length field.
		 */
		b0 = gen_cmp_gt(cstate, OR_LINKTYPE, 0, BPF_H, ETHERMTU);
		gen_not(b0);

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
			 * Check that the frame is an 802.2 frame
			 * (i.e., that the length/type field is
			 * a length field, <= ETHERMTU) and
			 * then check the DSAP.
			 */
			b0 = gen_cmp_gt(cstate, OR_LINKTYPE, 0, BPF_H, ETHERMTU);
			gen_not(b0);
			b1 = gen_cmp(cstate, OR_LINKTYPE, 2, BPF_B, (bpf_int32)proto);
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
			return gen_cmp(cstate, OR_LINKTYPE, 0, BPF_H,
			    (bpf_int32)proto);
		}
	}
}