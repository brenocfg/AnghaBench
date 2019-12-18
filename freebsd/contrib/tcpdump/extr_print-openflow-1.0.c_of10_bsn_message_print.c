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
#define  BSN_BW_CLEAR_DATA_REQUEST 142 
#define  BSN_BW_ENABLE_GET_REQUEST 141 
#define  BSN_GET_INTERFACES_REQUEST 140 
#define  BSN_GET_IP_MASK_REPLY 139 
#define  BSN_GET_IP_MASK_REQUEST 138 
#define  BSN_GET_L2_TABLE_REQUEST 137 
#define  BSN_GET_MIRRORING_REPLY 136 
#define  BSN_GET_MIRRORING_REQUEST 135 
#define  BSN_HYBRID_GET_REQUEST 134 
#define  BSN_SET_IP_MASK 133 
#define  BSN_SET_MIRRORING 132 
#define  BSN_SHELL_COMMAND 131 
#define  BSN_SHELL_OUTPUT 130 
#define  BSN_SHELL_STATUS 129 
#define  BSN_VIRTUAL_PORT_REMOVE_REQUEST 128 
 int EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int const) ; 
 int /*<<< orphan*/  bsn_onoff_str ; 
 int /*<<< orphan*/  bsn_subtype_str ; 
 int /*<<< orphan*/  fn_printn (int /*<<< orphan*/ *,int const*,int const,int const*) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_bsn_message_print(netdissect_options *ndo,
                       const u_char *cp, const u_char *ep, const u_int len)
{
	const u_char *cp0 = cp;
	uint32_t subtype;

	if (len < 4)
		goto invalid;
	/* subtype */
	ND_TCHECK2(*cp, 4);
	subtype = EXTRACT_32BITS(cp);
	cp += 4;
	ND_PRINT((ndo, "\n\t subtype %s", tok2str(bsn_subtype_str, "unknown (0x%08x)", subtype)));
	switch (subtype) {
	case BSN_GET_IP_MASK_REQUEST:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |     index     |                      pad                      |
		 * +---------------+---------------+---------------+---------------+
		 * |                              pad                              |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 12)
			goto invalid;
		/* index */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, ", index %u", *cp));
		cp += 1;
		/* pad */
		ND_TCHECK2(*cp, 7);
		cp += 7;
		break;
	case BSN_SET_IP_MASK:
	case BSN_GET_IP_MASK_REPLY:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |     index     |                      pad                      |
		 * +---------------+---------------+---------------+---------------+
		 * |                              mask                             |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 12)
			goto invalid;
		/* index */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, ", index %u", *cp));
		cp += 1;
		/* pad */
		ND_TCHECK2(*cp, 3);
		cp += 3;
		/* mask */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, ", mask %s", ipaddr_string(ndo, cp)));
		cp += 4;
		break;
	case BSN_SET_MIRRORING:
	case BSN_GET_MIRRORING_REQUEST:
	case BSN_GET_MIRRORING_REPLY:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * | report m. p.  |                      pad                      |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 8)
			goto invalid;
		/* report_mirror_ports */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, ", report_mirror_ports %s", tok2str(bsn_onoff_str, "bogus (%u)", *cp)));
		cp += 1;
		/* pad */
		ND_TCHECK2(*cp, 3);
		cp += 3;
		break;
	case BSN_GET_INTERFACES_REQUEST:
	case BSN_GET_L2_TABLE_REQUEST:
	case BSN_BW_ENABLE_GET_REQUEST:
	case BSN_BW_CLEAR_DATA_REQUEST:
	case BSN_HYBRID_GET_REQUEST:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 4)
			goto invalid;
		break;
	case BSN_VIRTUAL_PORT_REMOVE_REQUEST:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |                           vport_no                            |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 8)
			goto invalid;
		/* vport_no */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, ", vport_no %u", EXTRACT_32BITS(cp)));
		cp += 4;
		break;
	case BSN_SHELL_COMMAND:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |                            service                            |
		 * +---------------+---------------+---------------+---------------+
		 * |                             data ...
		 * +---------------+---------------+--------
		 *
		 */
		if (len < 8)
			goto invalid;
		/* service */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, ", service %u", EXTRACT_32BITS(cp)));
		cp += 4;
		/* data */
		ND_PRINT((ndo, ", data '"));
		if (fn_printn(ndo, cp, len - 8, ep)) {
			ND_PRINT((ndo, "'"));
			goto trunc;
		}
		ND_PRINT((ndo, "'"));
		cp += len - 8;
		break;
	case BSN_SHELL_OUTPUT:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |                             data ...
		 * +---------------+---------------+--------
		 *
		 */
		/* already checked that len >= 4 */
		/* data */
		ND_PRINT((ndo, ", data '"));
		if (fn_printn(ndo, cp, len - 4, ep)) {
			ND_PRINT((ndo, "'"));
			goto trunc;
		}
		ND_PRINT((ndo, "'"));
		cp += len - 4;
		break;
	case BSN_SHELL_STATUS:
		/*
		 *  0                   1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +---------------+---------------+---------------+---------------+
		 * |                            subtype                            |
		 * +---------------+---------------+---------------+---------------+
		 * |                            status                             |
		 * +---------------+---------------+---------------+---------------+
		 *
		 */
		if (len != 8)
			goto invalid;
		/* status */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, ", status 0x%08x", EXTRACT_32BITS(cp)));
		cp += 4;
		break;
	default:
		ND_TCHECK2(*cp, len - 4);
		cp += len - 4;
	}
	return cp;

invalid: /* skip the undersized data */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp0, len);
	return cp0 + len;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}