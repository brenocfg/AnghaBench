#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lladdr_info {int dummy; } ;
struct TYPE_28__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  ETHERTYPE_AARP 163 
#define  ETHERTYPE_AOE 162 
#define  ETHERTYPE_ARP 161 
#define  ETHERTYPE_ATALK 160 
#define  ETHERTYPE_CALM_FAST 159 
#define  ETHERTYPE_CFM 158 
#define  ETHERTYPE_CFM_OLD 157 
#define  ETHERTYPE_DN 156 
#define  ETHERTYPE_EAPOL 155 
#define  ETHERTYPE_GEONET 154 
#define  ETHERTYPE_GEONET_OLD 153 
#define  ETHERTYPE_IEEE1905_1 152 
#define  ETHERTYPE_IP 151 
#define  ETHERTYPE_IPV6 150 
#define  ETHERTYPE_IPX 149 
#define  ETHERTYPE_ISO 148 
#define  ETHERTYPE_LAT 147 
#define  ETHERTYPE_LLDP 146 
#define  ETHERTYPE_LOOPBACK 145 
#define  ETHERTYPE_MEDSA 144 
#define  ETHERTYPE_MOPDL 143 
#define  ETHERTYPE_MOPRC 142 
#define  ETHERTYPE_MPCP 141 
#define  ETHERTYPE_MPLS 140 
#define  ETHERTYPE_MPLS_MULTI 139 
#define  ETHERTYPE_MS_NLB_HB 138 
#define  ETHERTYPE_PPP 137 
#define  ETHERTYPE_PPPOED 136 
#define  ETHERTYPE_PPPOED2 135 
#define  ETHERTYPE_PPPOES 134 
#define  ETHERTYPE_PPPOES2 133 
#define  ETHERTYPE_REVARP 132 
#define  ETHERTYPE_RRCP 131 
#define  ETHERTYPE_SCA 130 
#define  ETHERTYPE_SLOW 129 
#define  ETHERTYPE_TIPC 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  aarp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aoe_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atalk_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calm_fast_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct lladdr_info const*) ; 
 int /*<<< orphan*/  cfm_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decnet_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geonet_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct lladdr_info const*) ; 
 int /*<<< orphan*/  ip6_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isoclns_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lldp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loopback_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  medsa_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lladdr_info const*,struct lladdr_info const*) ; 
 int /*<<< orphan*/  mpcp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpls_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msnlb_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ppp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppoe_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrcp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct lladdr_info const*,struct lladdr_info const*) ; 
 int /*<<< orphan*/  slow_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ethertype_print(netdissect_options *ndo,
                u_short ether_type, const u_char *p,
                u_int length, u_int caplen,
                const struct lladdr_info *src, const struct lladdr_info *dst)
{
	switch (ether_type) {

	case ETHERTYPE_IP:
	        ip_print(ndo, p, length);
		return (1);

	case ETHERTYPE_IPV6:
		ip6_print(ndo, p, length);
		return (1);

	case ETHERTYPE_ARP:
	case ETHERTYPE_REVARP:
	        arp_print(ndo, p, length, caplen);
		return (1);

	case ETHERTYPE_DN:
		decnet_print(ndo, p, length, caplen);
		return (1);

	case ETHERTYPE_ATALK:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo, "et1 "));
		atalk_print(ndo, p, length);
		return (1);

	case ETHERTYPE_AARP:
		aarp_print(ndo, p, length);
		return (1);

	case ETHERTYPE_IPX:
		ND_PRINT((ndo, "(NOV-ETHII) "));
		ipx_print(ndo, p, length);
		return (1);

	case ETHERTYPE_ISO:
		if (length == 0 || caplen == 0) {
			ND_PRINT((ndo, " [|osi]"));
			return (1);
		}
		isoclns_print(ndo, p + 1, length - 1);
		return(1);

	case ETHERTYPE_PPPOED:
	case ETHERTYPE_PPPOES:
	case ETHERTYPE_PPPOED2:
	case ETHERTYPE_PPPOES2:
		pppoe_print(ndo, p, length);
		return (1);

	case ETHERTYPE_EAPOL:
	        eap_print(ndo, p, length);
		return (1);

	case ETHERTYPE_RRCP:
	        rrcp_print(ndo, p, length, src, dst);
		return (1);

	case ETHERTYPE_PPP:
		if (length) {
			ND_PRINT((ndo, ": "));
			ppp_print(ndo, p, length);
		}
		return (1);

	case ETHERTYPE_MPCP:
	        mpcp_print(ndo, p, length);
		return (1);

	case ETHERTYPE_SLOW:
	        slow_print(ndo, p, length);
		return (1);

	case ETHERTYPE_CFM:
	case ETHERTYPE_CFM_OLD:
		cfm_print(ndo, p, length);
		return (1);

	case ETHERTYPE_LLDP:
		lldp_print(ndo, p, length);
		return (1);

        case ETHERTYPE_LOOPBACK:
		loopback_print(ndo, p, length);
                return (1);

	case ETHERTYPE_MPLS:
	case ETHERTYPE_MPLS_MULTI:
		mpls_print(ndo, p, length);
		return (1);

	case ETHERTYPE_TIPC:
		tipc_print(ndo, p, length, caplen);
		return (1);

	case ETHERTYPE_MS_NLB_HB:
		msnlb_print(ndo, p);
		return (1);

        case ETHERTYPE_GEONET_OLD:
        case ETHERTYPE_GEONET:
                geonet_print(ndo, p, length, src);
                return (1);

        case ETHERTYPE_CALM_FAST:
                calm_fast_print(ndo, p, length, src);
                return (1);

	case ETHERTYPE_AOE:
		aoe_print(ndo, p, length);
		return (1);

	case ETHERTYPE_MEDSA:
		medsa_print(ndo, p, length, caplen, src, dst);
		return (1);

	case ETHERTYPE_LAT:
	case ETHERTYPE_SCA:
	case ETHERTYPE_MOPRC:
	case ETHERTYPE_MOPDL:
	case ETHERTYPE_IEEE1905_1:
		/* default_print for now */
	default:
		return (0);
	}
}