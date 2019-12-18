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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  ETHERTYPE_IP 149 
#define  ETHERTYPE_IPV6 148 
#define  ETHERTYPE_IPX 147 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
#define  PPP_BACP 146 
#define  PPP_BAP 145 
#define  PPP_CCP 144 
#define  PPP_CHAP 143 
#define  PPP_COMP 142 
#define  PPP_IP 141 
#define  PPP_IPCP 140 
#define  PPP_IPV6 139 
#define  PPP_IPV6CP 138 
#define  PPP_IPX 137 
#define  PPP_LCP 136 
#define  PPP_ML 135 
#define  PPP_MPLSCP 134 
#define  PPP_MPLS_MCAST 133 
#define  PPP_MPLS_UCAST 132 
#define  PPP_OSI 131 
#define  PPP_OSICP 130 
#define  PPP_PAP 129 
#define  PPP_VJNC 128 
 int /*<<< orphan*/  handle_bap (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  handle_chap (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  handle_ctrl_proto (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  handle_mlppp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  handle_pap (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ip6_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ip_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ipx_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  isoclns_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mpls_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ppp_hdlc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ppptype2str ; 
 int /*<<< orphan*/  print_unknown_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
handle_ppp(netdissect_options *ndo,
           u_int proto, const u_char *p, int length)
{
	if ((proto & 0xff00) == 0x7e00) { /* is this an escape code ? */
		ppp_hdlc(ndo, p - 1, length);
		return;
	}

	switch (proto) {
	case PPP_LCP: /* fall through */
	case PPP_IPCP:
	case PPP_OSICP:
	case PPP_MPLSCP:
	case PPP_IPV6CP:
	case PPP_CCP:
	case PPP_BACP:
		handle_ctrl_proto(ndo, proto, p, length);
		break;
	case PPP_ML:
		handle_mlppp(ndo, p, length);
		break;
	case PPP_CHAP:
		handle_chap(ndo, p, length);
		break;
	case PPP_PAP:
		handle_pap(ndo, p, length);
		break;
	case PPP_BAP:		/* XXX: not yet completed */
		handle_bap(ndo, p, length);
		break;
	case ETHERTYPE_IP:	/*XXX*/
        case PPP_VJNC:
	case PPP_IP:
		ip_print(ndo, p, length);
		break;
	case ETHERTYPE_IPV6:	/*XXX*/
	case PPP_IPV6:
		ip6_print(ndo, p, length);
		break;
	case ETHERTYPE_IPX:	/*XXX*/
	case PPP_IPX:
		ipx_print(ndo, p, length);
		break;
	case PPP_OSI:
		isoclns_print(ndo, p, length);
		break;
	case PPP_MPLS_UCAST:
	case PPP_MPLS_MCAST:
		mpls_print(ndo, p, length);
		break;
	case PPP_COMP:
		ND_PRINT((ndo, "compressed PPP data"));
		break;
	default:
		ND_PRINT((ndo, "%s ", tok2str(ppptype2str, "unknown PPP protocol (0x%04x)", proto)));
		print_unknown_data(ndo, p, "\n\t", length);
		break;
	}
}