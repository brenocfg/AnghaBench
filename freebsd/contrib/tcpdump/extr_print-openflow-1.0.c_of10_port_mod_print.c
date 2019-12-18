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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  OFPPC_U ; 
 int /*<<< orphan*/  OFPPF_U ; 
 int /*<<< orphan*/  etheraddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  of10_bitmap_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofpp_str ; 
 int /*<<< orphan*/  ofppc_bm ; 
 int /*<<< orphan*/  ofppf_bm ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_port_mod_print(netdissect_options *ndo,
                    const u_char *cp, const u_char *ep)
{
	/* port_no */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, "\n\t port_no %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
	cp += 2;
	/* hw_addr */
	ND_TCHECK2(*cp, ETHER_ADDR_LEN);
	ND_PRINT((ndo, ", hw_addr %s", etheraddr_string(ndo, cp)));
	cp += ETHER_ADDR_LEN;
	/* config */
	ND_TCHECK2(*cp, 4);
	ND_PRINT((ndo, "\n\t config 0x%08x", EXTRACT_32BITS(cp)));
	of10_bitmap_print(ndo, ofppc_bm, EXTRACT_32BITS(cp), OFPPC_U);
	cp += 4;
	/* mask */
	ND_TCHECK2(*cp, 4);
	ND_PRINT((ndo, "\n\t mask 0x%08x", EXTRACT_32BITS(cp)));
	of10_bitmap_print(ndo, ofppc_bm, EXTRACT_32BITS(cp), OFPPC_U);
	cp += 4;
	/* advertise */
	ND_TCHECK2(*cp, 4);
	ND_PRINT((ndo, "\n\t advertise 0x%08x", EXTRACT_32BITS(cp)));
	of10_bitmap_print(ndo, ofppf_bm, EXTRACT_32BITS(cp), OFPPF_U);
	cp += 4;
	/* pad */
	ND_TCHECK2(*cp, 4);
	return cp + 4;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}