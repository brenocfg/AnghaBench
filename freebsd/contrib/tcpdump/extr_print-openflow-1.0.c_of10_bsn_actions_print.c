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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  BSN_ACTION_MIRROR 129 
#define  ETHERTYPE_8021Q 128 
 int EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int const) ; 
 int /*<<< orphan*/  bsn_action_subtype_str ; 
 int /*<<< orphan*/  bsn_mirror_copy_stage_str ; 
 int /*<<< orphan*/  ieee8021q_tci_string (int) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_bsn_actions_print(netdissect_options *ndo,
                       const u_char *cp, const u_char *ep, const u_int len)
{
	const u_char *cp0 = cp;
	uint32_t subtype, vlan_tag;

	if (len < 4)
		goto invalid;
	/* subtype */
	ND_TCHECK2(*cp, 4);
	subtype = EXTRACT_32BITS(cp);
	cp += 4;
	ND_PRINT((ndo, "\n\t  subtype %s", tok2str(bsn_action_subtype_str, "unknown (0x%08x)", subtype)));
	switch (subtype) {
	case BSN_ACTION_MIRROR:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |                           dest_port                           |
		 * +---------------+---------------+---------------+---------------+
		 * |                           vlan_tag                            |
		 * +---------------+---------------+---------------+---------------+
		 * |  copy_stage   |                      pad                      |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 16)
			goto invalid;
		/* dest_port */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, ", dest_port %u", EXTRACT_32BITS(cp)));
		cp += 4;
		/* vlan_tag */
		ND_TCHECK2(*cp, 4);
		vlan_tag = EXTRACT_32BITS(cp);
		cp += 4;
		switch (vlan_tag >> 16) {
		case 0:
			ND_PRINT((ndo, ", vlan_tag none"));
			break;
		case ETHERTYPE_8021Q:
			ND_PRINT((ndo, ", vlan_tag 802.1Q (%s)", ieee8021q_tci_string(vlan_tag & 0xffff)));
			break;
		default:
			ND_PRINT((ndo, ", vlan_tag unknown (0x%04x)", vlan_tag >> 16));
		}
		/* copy_stage */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, ", copy_stage %s", tok2str(bsn_mirror_copy_stage_str, "unknown (%u)", *cp)));
		cp += 1;
		/* pad */
		ND_TCHECK2(*cp, 3);
		cp += 3;
		break;
	default:
		ND_TCHECK2(*cp, len - 4);
		cp += len - 4;
	}

	return cp;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp0, len);
	return cp0 + len;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}