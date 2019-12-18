#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lladdr_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  (* addr_string ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int ETHERTYPE_ATALK ; 
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int EXTRACT_24BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
#define  OUI_APPLETALK 145 
#define  OUI_CISCO 144 
#define  OUI_CISCO_90 143 
#define  OUI_ENCAP_ETHER 142 
#define  OUI_RFC2684 141 
#define  PID_CISCO_CDP 140 
#define  PID_CISCO_DTP 139 
#define  PID_CISCO_PVST 138 
#define  PID_CISCO_UDLD 137 
#define  PID_CISCO_VLANBRIDGE 136 
#define  PID_CISCO_VTP 135 
#define  PID_RFC2684_802_5_FCS 134 
#define  PID_RFC2684_802_5_NOFCS 133 
#define  PID_RFC2684_BPDU 132 
#define  PID_RFC2684_ETH_FCS 131 
#define  PID_RFC2684_ETH_NOFCS 130 
#define  PID_RFC2684_FDDI_FCS 129 
#define  PID_RFC2684_FDDI_NOFCS 128 
 int /*<<< orphan*/  cdp_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  dtp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ether_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ethertype_print (TYPE_1__*,int,int /*<<< orphan*/  const*,int,int,struct lladdr_info const*,struct lladdr_info const*) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  fddi_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  oui_to_struct_tok (int) ; 
 int /*<<< orphan*/  oui_values ; 
 int /*<<< orphan*/  stp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  token_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  udld_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  vtp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

int
snap_print(netdissect_options *ndo, const u_char *p, u_int length, u_int caplen,
	const struct lladdr_info *src, const struct lladdr_info *dst,
	u_int bridge_pad)
{
	uint32_t orgcode;
	register u_short et;
	register int ret;

	ND_TCHECK2(*p, 5);
	if (caplen < 5 || length < 5)
		goto trunc;
	orgcode = EXTRACT_24BITS(p);
	et = EXTRACT_16BITS(p + 3);

	if (ndo->ndo_eflag) {
		/*
		 * Somebody's already printed the MAC addresses, if there
		 * are any, so just print the SNAP header, not the MAC
		 * addresses.
		 */
		ND_PRINT((ndo, "oui %s (0x%06x), %s %s (0x%04x), length %u: ",
		     tok2str(oui_values, "Unknown", orgcode),
		     orgcode,
		     (orgcode == 0x000000 ? "ethertype" : "pid"),
		     tok2str(oui_to_struct_tok(orgcode), "Unknown", et),
		     et, length - 5));
	}
	p += 5;
	length -= 5;
	caplen -= 5;

	switch (orgcode) {
	case OUI_ENCAP_ETHER:
	case OUI_CISCO_90:
		/*
		 * This is an encapsulated Ethernet packet,
		 * or a packet bridged by some piece of
		 * Cisco hardware; the protocol ID is
		 * an Ethernet protocol type.
		 */
		ret = ethertype_print(ndo, et, p, length, caplen, src, dst);
		if (ret)
			return (ret);
		break;

	case OUI_APPLETALK:
		if (et == ETHERTYPE_ATALK) {
			/*
			 * No, I have no idea why Apple used one
			 * of their own OUIs, rather than
			 * 0x000000, and an Ethernet packet
			 * type, for Appletalk data packets,
			 * but used 0x000000 and an Ethernet
			 * packet type for AARP packets.
			 */
			ret = ethertype_print(ndo, et, p, length, caplen, src, dst);
			if (ret)
				return (ret);
		}
		break;

	case OUI_CISCO:
                switch (et) {
                case PID_CISCO_CDP:
                        cdp_print(ndo, p, length, caplen);
                        return (1);
                case PID_CISCO_DTP:
                        dtp_print(ndo, p, length);
                        return (1);
                case PID_CISCO_UDLD:
                        udld_print(ndo, p, length);
                        return (1);
                case PID_CISCO_VTP:
                        vtp_print(ndo, p, length);
                        return (1);
                case PID_CISCO_PVST:
                case PID_CISCO_VLANBRIDGE:
                        stp_print(ndo, p, length);
                        return (1);
                default:
                        break;
                }
		break;

	case OUI_RFC2684:
		switch (et) {

		case PID_RFC2684_ETH_FCS:
		case PID_RFC2684_ETH_NOFCS:
			/*
			 * XXX - remove the last two bytes for
			 * PID_RFC2684_ETH_FCS?
			 */
			/*
			 * Skip the padding.
			 */
			ND_TCHECK2(*p, bridge_pad);
			caplen -= bridge_pad;
			length -= bridge_pad;
			p += bridge_pad;

			/*
			 * What remains is an Ethernet packet.
			 */
			ether_print(ndo, p, length, caplen, NULL, NULL);
			return (1);

		case PID_RFC2684_802_5_FCS:
		case PID_RFC2684_802_5_NOFCS:
			/*
			 * XXX - remove the last two bytes for
			 * PID_RFC2684_ETH_FCS?
			 */
			/*
			 * Skip the padding, but not the Access
			 * Control field.
			 */
			ND_TCHECK2(*p, bridge_pad);
			caplen -= bridge_pad;
			length -= bridge_pad;
			p += bridge_pad;

			/*
			 * What remains is an 802.5 Token Ring
			 * packet.
			 */
			token_print(ndo, p, length, caplen);
			return (1);

		case PID_RFC2684_FDDI_FCS:
		case PID_RFC2684_FDDI_NOFCS:
			/*
			 * XXX - remove the last two bytes for
			 * PID_RFC2684_ETH_FCS?
			 */
			/*
			 * Skip the padding.
			 */
			ND_TCHECK2(*p, bridge_pad + 1);
			caplen -= bridge_pad + 1;
			length -= bridge_pad + 1;
			p += bridge_pad + 1;

			/*
			 * What remains is an FDDI packet.
			 */
			fddi_print(ndo, p, length, caplen);
			return (1);

		case PID_RFC2684_BPDU:
			stp_print(ndo, p, length);
			return (1);
		}
	}
	if (!ndo->ndo_eflag) {
		/*
		 * Nobody printed the link-layer addresses, so print them, if
		 * we have any.
		 */
		if (src != NULL && dst != NULL) {
			ND_PRINT((ndo, "%s > %s ",
				(src->addr_string)(ndo, src->addr),
				(dst->addr_string)(ndo, dst->addr)));
		}
		/*
		 * Print the SNAP header, but if the OUI is 000000, don't
		 * bother printing it, and report the PID as being an
		 * ethertype.
		 */
		if (orgcode == 0x000000) {
			ND_PRINT((ndo, "SNAP, ethertype %s (0x%04x), length %u: ",
			     tok2str(ethertype_values, "Unknown", et),
			     et, length));
		} else {
			ND_PRINT((ndo, "SNAP, oui %s (0x%06x), pid %s (0x%04x), length %u: ",
			     tok2str(oui_values, "Unknown", orgcode),
			     orgcode,
			     tok2str(oui_to_struct_tok(orgcode), "Unknown", et),
			     et, length));
		}
	}
	return (0);

trunc:
	ND_PRINT((ndo, "[|snap]"));
	return (1);
}