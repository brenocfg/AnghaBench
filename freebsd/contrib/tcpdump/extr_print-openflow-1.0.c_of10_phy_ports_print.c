#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ const ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,scalar_t__ const) ; 
 int /*<<< orphan*/  OFPPC_U ; 
 int /*<<< orphan*/  OFPPF_U ; 
 int /*<<< orphan*/  OFPPS_U ; 
 int OFP_MAX_PORT_NAME_LEN ; 
 scalar_t__ OF_PHY_PORT_LEN ; 
 int /*<<< orphan*/  etheraddr_string (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fn_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  of10_bitmap_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofpp_str ; 
 int /*<<< orphan*/  ofppc_bm ; 
 int /*<<< orphan*/  ofppf_bm ; 
 int /*<<< orphan*/  ofpps_bm ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_phy_ports_print(netdissect_options *ndo,
                     const u_char *cp, const u_char *ep, u_int len)
{
	const u_char *cp0 = cp;
	const u_int len0 = len;

	while (len) {
		if (len < OF_PHY_PORT_LEN)
			goto invalid;
		/* port_no */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, "\n\t  port_no %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
		cp += 2;
		/* hw_addr */
		ND_TCHECK2(*cp, ETHER_ADDR_LEN);
		ND_PRINT((ndo, ", hw_addr %s", etheraddr_string(ndo, cp)));
		cp += ETHER_ADDR_LEN;
		/* name */
		ND_TCHECK2(*cp, OFP_MAX_PORT_NAME_LEN);
		ND_PRINT((ndo, ", name '"));
		fn_print(ndo, cp, cp + OFP_MAX_PORT_NAME_LEN);
		ND_PRINT((ndo, "'"));
		cp += OFP_MAX_PORT_NAME_LEN;

		if (ndo->ndo_vflag < 2) {
			ND_TCHECK2(*cp, 24);
			cp += 24;
			goto next_port;
		}
		/* config */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t   config 0x%08x", EXTRACT_32BITS(cp)));
		of10_bitmap_print(ndo, ofppc_bm, EXTRACT_32BITS(cp), OFPPC_U);
		cp += 4;
		/* state */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t   state 0x%08x", EXTRACT_32BITS(cp)));
		of10_bitmap_print(ndo, ofpps_bm, EXTRACT_32BITS(cp), OFPPS_U);
		cp += 4;
		/* curr */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t   curr 0x%08x", EXTRACT_32BITS(cp)));
		of10_bitmap_print(ndo, ofppf_bm, EXTRACT_32BITS(cp), OFPPF_U);
		cp += 4;
		/* advertised */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t   advertised 0x%08x", EXTRACT_32BITS(cp)));
		of10_bitmap_print(ndo, ofppf_bm, EXTRACT_32BITS(cp), OFPPF_U);
		cp += 4;
		/* supported */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t   supported 0x%08x", EXTRACT_32BITS(cp)));
		of10_bitmap_print(ndo, ofppf_bm, EXTRACT_32BITS(cp), OFPPF_U);
		cp += 4;
		/* peer */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t   peer 0x%08x", EXTRACT_32BITS(cp)));
		of10_bitmap_print(ndo, ofppf_bm, EXTRACT_32BITS(cp), OFPPF_U);
		cp += 4;
next_port:
		len -= OF_PHY_PORT_LEN;
	} /* while */
	return cp;

invalid: /* skip the undersized trailing data */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp0, len0);
	return cp0 + len0;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}