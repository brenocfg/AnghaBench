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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ const ETHER_ADDR_LEN ; 
 scalar_t__ EXTRACT_16BITS (int const*) ; 
 scalar_t__ EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,scalar_t__ const) ; 
#define  OFPAT_ENQUEUE 140 
#define  OFPAT_OUTPUT 139 
#define  OFPAT_SET_DL_DST 138 
#define  OFPAT_SET_DL_SRC 137 
#define  OFPAT_SET_NW_DST 136 
#define  OFPAT_SET_NW_SRC 135 
#define  OFPAT_SET_NW_TOS 134 
#define  OFPAT_SET_TP_DST 133 
#define  OFPAT_SET_TP_SRC 132 
#define  OFPAT_SET_VLAN_PCP 131 
#define  OFPAT_SET_VLAN_VID 130 
#define  OFPAT_STRIP_VLAN 129 
#define  OFPAT_VENDOR 128 
 scalar_t__ OFPP_CONTROLLER ; 
 scalar_t__ OF_ACTION_HEADER_LEN ; 
 int /*<<< orphan*/  etheraddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  istr ; 
 int* of10_vendor_action_print (int /*<<< orphan*/ *,int const*,int const*,scalar_t__) ; 
 int /*<<< orphan*/  ofpat_str ; 
 int /*<<< orphan*/  ofpp_str ; 
 int /*<<< orphan*/  ofpq_str ; 
 int /*<<< orphan*/  pcp_str (int const) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  vlan_str (scalar_t__) ; 

__attribute__((used)) static const u_char *
of10_actions_print(netdissect_options *ndo,
                   const char *pfx, const u_char *cp, const u_char *ep,
                   u_int len)
{
	const u_char *cp0 = cp;
	const u_int len0 = len;
	uint16_t type, alen, output_port;

	while (len) {
		u_char alen_bogus = 0, skip = 0;

		if (len < OF_ACTION_HEADER_LEN)
			goto invalid;
		/* type */
		ND_TCHECK2(*cp, 2);
		type = EXTRACT_16BITS(cp);
		cp += 2;
		ND_PRINT((ndo, "%saction type %s", pfx, tok2str(ofpat_str, "invalid (0x%04x)", type)));
		/* length */
		ND_TCHECK2(*cp, 2);
		alen = EXTRACT_16BITS(cp);
		cp += 2;
		ND_PRINT((ndo, ", len %u", alen));
		/* On action size underrun/overrun skip the rest of the action list. */
		if (alen < OF_ACTION_HEADER_LEN || alen > len)
			goto invalid;
		/* On action size inappropriate for the given type or invalid type just skip
		 * the current action, as the basic length constraint has been met. */
		switch (type) {
		case OFPAT_OUTPUT:
		case OFPAT_SET_VLAN_VID:
		case OFPAT_SET_VLAN_PCP:
		case OFPAT_STRIP_VLAN:
		case OFPAT_SET_NW_SRC:
		case OFPAT_SET_NW_DST:
		case OFPAT_SET_NW_TOS:
		case OFPAT_SET_TP_SRC:
		case OFPAT_SET_TP_DST:
			alen_bogus = alen != 8;
			break;
		case OFPAT_SET_DL_SRC:
		case OFPAT_SET_DL_DST:
		case OFPAT_ENQUEUE:
			alen_bogus = alen != 16;
			break;
		case OFPAT_VENDOR:
			alen_bogus = alen % 8 != 0; /* already >= 8 so far */
			break;
		default:
			skip = 1;
		}
		if (alen_bogus) {
			ND_PRINT((ndo, " (bogus)"));
			skip = 1;
		}
		if (skip) {
			ND_TCHECK2(*cp, alen - 4);
			cp += alen - 4;
			goto next_action;
		}
		/* OK to decode the rest of the action structure */
		switch (type) {
		case OFPAT_OUTPUT:
			/* port */
			ND_TCHECK2(*cp, 2);
			output_port = EXTRACT_16BITS(cp);
			cp += 2;
			ND_PRINT((ndo, ", port %s", tok2str(ofpp_str, "%u", output_port)));
			/* max_len */
			ND_TCHECK2(*cp, 2);
			if (output_port == OFPP_CONTROLLER)
				ND_PRINT((ndo, ", max_len %u", EXTRACT_16BITS(cp)));
			cp += 2;
			break;
		case OFPAT_SET_VLAN_VID:
			/* vlan_vid */
			ND_TCHECK2(*cp, 2);
			ND_PRINT((ndo, ", vlan_vid %s", vlan_str(EXTRACT_16BITS(cp))));
			cp += 2;
			/* pad */
			ND_TCHECK2(*cp, 2);
			cp += 2;
			break;
		case OFPAT_SET_VLAN_PCP:
			/* vlan_pcp */
			ND_TCHECK2(*cp, 1);
			ND_PRINT((ndo, ", vlan_pcp %s", pcp_str(*cp)));
			cp += 1;
			/* pad */
			ND_TCHECK2(*cp, 3);
			cp += 3;
			break;
		case OFPAT_SET_DL_SRC:
		case OFPAT_SET_DL_DST:
			/* dl_addr */
			ND_TCHECK2(*cp, ETHER_ADDR_LEN);
			ND_PRINT((ndo, ", dl_addr %s", etheraddr_string(ndo, cp)));
			cp += ETHER_ADDR_LEN;
			/* pad */
			ND_TCHECK2(*cp, 6);
			cp += 6;
			break;
		case OFPAT_SET_NW_SRC:
		case OFPAT_SET_NW_DST:
			/* nw_addr */
			ND_TCHECK2(*cp, 4);
			ND_PRINT((ndo, ", nw_addr %s", ipaddr_string(ndo, cp)));
			cp += 4;
			break;
		case OFPAT_SET_NW_TOS:
			/* nw_tos */
			ND_TCHECK2(*cp, 1);
			ND_PRINT((ndo, ", nw_tos 0x%02x", *cp));
			cp += 1;
			/* pad */
			ND_TCHECK2(*cp, 3);
			cp += 3;
			break;
		case OFPAT_SET_TP_SRC:
		case OFPAT_SET_TP_DST:
			/* nw_tos */
			ND_TCHECK2(*cp, 2);
			ND_PRINT((ndo, ", tp_port %u", EXTRACT_16BITS(cp)));
			cp += 2;
			/* pad */
			ND_TCHECK2(*cp, 2);
			cp += 2;
			break;
		case OFPAT_ENQUEUE:
			/* port */
			ND_TCHECK2(*cp, 2);
			ND_PRINT((ndo, ", port %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
			cp += 2;
			/* pad */
			ND_TCHECK2(*cp, 6);
			cp += 6;
			/* queue_id */
			ND_TCHECK2(*cp, 4);
			ND_PRINT((ndo, ", queue_id %s", tok2str(ofpq_str, "%u", EXTRACT_32BITS(cp))));
			cp += 4;
			break;
		case OFPAT_VENDOR:
			if (ep == (cp = of10_vendor_action_print(ndo, cp, ep, alen - 4)))
				return ep; /* end of snapshot */
			break;
		case OFPAT_STRIP_VLAN:
			/* pad */
			ND_TCHECK2(*cp, 4);
			cp += 4;
			break;
		} /* switch */
next_action:
		len -= alen;
	} /* while */
	return cp;

invalid: /* skip the rest of actions */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp0, len0);
	return cp0 + len0;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}