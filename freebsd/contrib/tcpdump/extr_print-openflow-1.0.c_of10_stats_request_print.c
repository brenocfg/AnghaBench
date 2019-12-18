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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int const EXTRACT_16BITS (int const*) ; 
 int const EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int const) ; 
#define  OFPST_AGGREGATE 134 
#define  OFPST_DESC 133 
#define  OFPST_FLOW 132 
#define  OFPST_PORT 131 
#define  OFPST_QUEUE 130 
#define  OFPST_TABLE 129 
#define  OFPST_VENDOR 128 
 int OF_FLOW_STATS_REQUEST_LEN ; 
 int OF_PORT_STATS_REQUEST_LEN ; 
 int OF_QUEUE_STATS_REQUEST_LEN ; 
 scalar_t__ OF_STATS_REQUEST_LEN ; 
 int /*<<< orphan*/  istr ; 
 int* of10_match_print (int /*<<< orphan*/ *,char*,int const*,int const*) ; 
 int const* of10_vendor_data_print (int /*<<< orphan*/ *,int const*,int const*,int) ; 
 int /*<<< orphan*/  ofpp_str ; 
 int /*<<< orphan*/  ofpq_str ; 
 int /*<<< orphan*/  ofpst_str ; 
 int /*<<< orphan*/  tableid_str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_stats_request_print(netdissect_options *ndo,
                         const u_char *cp, const u_char *ep, u_int len)
{
	const u_char *cp0 = cp;
	const u_int len0 = len;
	uint16_t type;

	/* type */
	ND_TCHECK2(*cp, 2);
	type = EXTRACT_16BITS(cp);
	cp += 2;
	ND_PRINT((ndo, "\n\t type %s", tok2str(ofpst_str, "invalid (0x%04x)", type)));
	/* flags */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, ", flags 0x%04x", EXTRACT_16BITS(cp)));
	if (EXTRACT_16BITS(cp))
		ND_PRINT((ndo, " (bogus)"));
	cp += 2;
	/* type-specific body of one of fixed lengths */
	len -= OF_STATS_REQUEST_LEN;
	switch(type) {
	case OFPST_DESC:
	case OFPST_TABLE:
		if (len)
			goto invalid;
		return cp;
	case OFPST_FLOW:
	case OFPST_AGGREGATE:
		if (len != OF_FLOW_STATS_REQUEST_LEN)
			goto invalid;
		/* match */
		if (ep == (cp = of10_match_print(ndo, "\n\t ", cp, ep)))
			return ep; /* end of snapshot */
		/* table_id */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, "\n\t table_id %s", tok2str(tableid_str, "%u", *cp)));
		cp += 1;
		/* pad */
		ND_TCHECK2(*cp, 1);
		cp += 1;
		/* out_port */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, ", out_port %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
		return cp + 2;
	case OFPST_PORT:
		if (len != OF_PORT_STATS_REQUEST_LEN)
			goto invalid;
		/* port_no */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, "\n\t port_no %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
		cp += 2;
		/* pad */
		ND_TCHECK2(*cp, 6);
		return cp + 6;
	case OFPST_QUEUE:
		if (len != OF_QUEUE_STATS_REQUEST_LEN)
			goto invalid;
		/* port_no */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, "\n\t port_no %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
		cp += 2;
		/* pad */
		ND_TCHECK2(*cp, 2);
		cp += 2;
		/* queue_id */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, ", queue_id %s", tok2str(ofpq_str, "%u", EXTRACT_32BITS(cp))));
		return cp + 4;
	case OFPST_VENDOR:
		return of10_vendor_data_print(ndo, cp, ep, len);
	}
	return cp;

invalid: /* skip the message body */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp0, len0);
	return cp0 + len0;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}