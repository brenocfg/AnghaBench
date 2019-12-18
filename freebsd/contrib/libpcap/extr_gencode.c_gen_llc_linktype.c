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
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_H ; 
 int ETHERMTU ; 
#define  ETHERTYPE_ATALK 132 
#define  LLCSAP_IP 131 
#define  LLCSAP_IPX 130 
#define  LLCSAP_ISONS 129 
#define  LLCSAP_NETBEUI 128 
 int /*<<< orphan*/  OR_LLC ; 
 struct block* gen_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_snap (int /*<<< orphan*/ *,int,int const) ; 

__attribute__((used)) static struct block *
gen_llc_linktype(compiler_state_t *cstate, int proto)
{
	/*
	 * XXX - handle token-ring variable-length header.
	 */
	switch (proto) {

	case LLCSAP_IP:
	case LLCSAP_ISONS:
	case LLCSAP_NETBEUI:
		/*
		 * XXX - should we check both the DSAP and the
		 * SSAP, like this, or should we check just the
		 * DSAP, as we do for other SAP values?
		 */
		return gen_cmp(cstate, OR_LLC, 0, BPF_H, (bpf_u_int32)
			     ((proto << 8) | proto));

	case LLCSAP_IPX:
		/*
		 * XXX - are there ever SNAP frames for IPX on
		 * non-Ethernet 802.x networks?
		 */
		return gen_cmp(cstate, OR_LLC, 0, BPF_B,
		    (bpf_int32)LLCSAP_IPX);

	case ETHERTYPE_ATALK:
		/*
		 * 802.2-encapsulated ETHERTYPE_ATALK packets are
		 * SNAP packets with an organization code of
		 * 0x080007 (Apple, for Appletalk) and a protocol
		 * type of ETHERTYPE_ATALK (Appletalk).
		 *
		 * XXX - check for an organization code of
		 * encapsulated Ethernet as well?
		 */
		return gen_snap(cstate, 0x080007, ETHERTYPE_ATALK);

	default:
		/*
		 * XXX - we don't have to check for IPX 802.3
		 * here, but should we check for the IPX Ethertype?
		 */
		if (proto <= ETHERMTU) {
			/*
			 * This is an LLC SAP value, so check
			 * the DSAP.
			 */
			return gen_cmp(cstate, OR_LLC, 0, BPF_B, (bpf_int32)proto);
		} else {
			/*
			 * This is an Ethernet type; we assume that it's
			 * unlikely that it'll appear in the right place
			 * at random, and therefore check only the
			 * location that would hold the Ethernet type
			 * in a SNAP frame with an organization code of
			 * 0x000000 (encapsulated Ethernet).
			 *
			 * XXX - if we were to check for the SNAP DSAP and
			 * LSAP, as per XXX, and were also to check for an
			 * organization code of 0x000000 (encapsulated
			 * Ethernet), we'd do
			 *
			 *	return gen_snap(cstate, 0x000000, proto);
			 *
			 * here; for now, we don't, as per the above.
			 * I don't know whether it's worth the extra CPU
			 * time to do the right check or not.
			 */
			return gen_cmp(cstate, OR_LLC, 6, BPF_H, (bpf_int32)proto);
		}
	}
}