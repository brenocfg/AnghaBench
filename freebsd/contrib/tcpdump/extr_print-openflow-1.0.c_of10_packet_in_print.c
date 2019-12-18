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
 int /*<<< orphan*/  const EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int OF_PACKET_IN_LEN ; 
 int /*<<< orphan*/  bufferid_str ; 
 int /*<<< orphan*/  const* of10_packet_data_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  ofpp_str ; 
 int /*<<< orphan*/  ofpr_str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_packet_in_print(netdissect_options *ndo,
                     const u_char *cp, const u_char *ep, const u_int len)
{
	/* buffer_id */
	ND_TCHECK2(*cp, 4);
	ND_PRINT((ndo, "\n\t buffer_id %s", tok2str(bufferid_str, "0x%08x", EXTRACT_32BITS(cp))));
	cp += 4;
	/* total_len */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, ", total_len %u", EXTRACT_16BITS(cp)));
	cp += 2;
	/* in_port */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, ", in_port %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
	cp += 2;
	/* reason */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", reason %s", tok2str(ofpr_str, "invalid (0x%02x)", *cp)));
	cp += 1;
	/* pad */
	ND_TCHECK2(*cp, 1);
	cp += 1;
	/* data */
	/* 2 mock octets count in OF_PACKET_IN_LEN but not in len */
	return of10_packet_data_print(ndo, cp, ep, len - (OF_PACKET_IN_LEN - 2));

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}