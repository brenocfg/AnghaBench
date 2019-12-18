#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_17__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int const EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int const) ; 
#define  OFPT_BARRIER_REPLY 149 
#define  OFPT_BARRIER_REQUEST 148 
#define  OFPT_ECHO_REPLY 147 
#define  OFPT_ECHO_REQUEST 146 
#define  OFPT_ERROR 145 
#define  OFPT_FEATURES_REPLY 144 
#define  OFPT_FEATURES_REQUEST 143 
#define  OFPT_FLOW_MOD 142 
#define  OFPT_FLOW_REMOVED 141 
#define  OFPT_GET_CONFIG_REPLY 140 
#define  OFPT_GET_CONFIG_REQUEST 139 
#define  OFPT_HELLO 138 
#define  OFPT_PACKET_IN 137 
#define  OFPT_PACKET_OUT 136 
#define  OFPT_PORT_MOD 135 
#define  OFPT_PORT_STATUS 134 
#define  OFPT_QUEUE_GET_CONFIG_REPLY 133 
#define  OFPT_QUEUE_GET_CONFIG_REQUEST 132 
#define  OFPT_SET_CONFIG 131 
#define  OFPT_STATS_REPLY 130 
#define  OFPT_STATS_REQUEST 129 
#define  OFPT_VENDOR 128 
 int const OF_ERROR_MSG_LEN ; 
 int const OF_FLOW_MOD_LEN ; 
 int const OF_FLOW_REMOVED_LEN ; 
 int const OF_HEADER_LEN ; 
 int /*<<< orphan*/  OF_PACKET_IN_LEN ; 
 int const OF_PACKET_OUT_LEN ; 
 int /*<<< orphan*/  OF_PHY_PORT_LEN ; 
 int const OF_PORT_MOD_LEN ; 
 int const OF_PORT_STATUS_LEN ; 
 int const OF_QUEUE_GET_CONFIG_REPLY_LEN ; 
 int const OF_QUEUE_GET_CONFIG_REQUEST_LEN ; 
 int const OF_STATS_REPLY_LEN ; 
 int const OF_STATS_REQUEST_LEN ; 
 int const OF_SWITCH_CONFIG_LEN ; 
 int const OF_SWITCH_FEATURES_LEN ; 
 int const OF_VENDOR_HEADER_LEN ; 
 int /*<<< orphan*/  istr ; 
 int const* of10_data_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_error_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_features_reply_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_flow_mod_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_flow_removed_print (TYPE_1__*,int const*,int const*) ; 
 int const* of10_packet_in_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_packet_out_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_phy_ports_print (TYPE_1__*,int const*,int const*,int /*<<< orphan*/ ) ; 
 int const* of10_port_mod_print (TYPE_1__*,int const*,int const*) ; 
 int const* of10_queues_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_stats_reply_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_stats_request_print (TYPE_1__*,int const*,int const*,int const) ; 
 int const* of10_vendor_message_print (TYPE_1__*,int const*,int const*,int const) ; 
 int /*<<< orphan*/  ofp_config_str ; 
 int /*<<< orphan*/  ofpp_str ; 
 int /*<<< orphan*/  ofppr_str ; 
 int /*<<< orphan*/  ofpt_str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

const u_char *
of10_header_body_print(netdissect_options *ndo,
                       const u_char *cp, const u_char *ep, const uint8_t type,
                       const uint16_t len, const uint32_t xid)
{
	const u_char *cp0 = cp;
	const u_int len0 = len;
	/* Thus far message length is not less than the basic header size, but most
	 * message types have additional assorted constraints on the length. Wherever
	 * possible, check that message length meets the constraint, in remaining
	 * cases check that the length is OK to begin decoding and leave any final
	 * verification up to a lower-layer function. When the current message is
	 * invalid, proceed to the next message. */

	/* [OF10] Section 5.1 */
	ND_PRINT((ndo, "\n\tversion 1.0, type %s, length %u, xid 0x%08x",
	       tok2str(ofpt_str, "invalid (0x%02x)", type), len, xid));
	switch (type) {
	/* OpenFlow header only. */
	case OFPT_FEATURES_REQUEST: /* [OF10] Section 5.3.1 */
	case OFPT_GET_CONFIG_REQUEST: /* [OF10] Section 5.3.2 */
	case OFPT_BARRIER_REQUEST: /* [OF10] Section 5.3.7 */
	case OFPT_BARRIER_REPLY: /* ibid */
		if (len != OF_HEADER_LEN)
			goto invalid;
		break;

	/* OpenFlow header and fixed-size message body. */
	case OFPT_SET_CONFIG: /* [OF10] Section 5.3.2 */
	case OFPT_GET_CONFIG_REPLY: /* ibid */
		if (len != OF_SWITCH_CONFIG_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		/* flags */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, "\n\t flags %s", tok2str(ofp_config_str, "invalid (0x%04x)", EXTRACT_16BITS(cp))));
		cp += 2;
		/* miss_send_len */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, ", miss_send_len %u", EXTRACT_16BITS(cp)));
		return cp + 2;
	case OFPT_PORT_MOD:
		if (len != OF_PORT_MOD_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_port_mod_print(ndo, cp, ep);
	case OFPT_QUEUE_GET_CONFIG_REQUEST: /* [OF10] Section 5.3.4 */
		if (len != OF_QUEUE_GET_CONFIG_REQUEST_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		/* port */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, "\n\t port_no %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
		cp += 2;
		/* pad */
		ND_TCHECK2(*cp, 2);
		return cp + 2;
	case OFPT_FLOW_REMOVED:
		if (len != OF_FLOW_REMOVED_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_flow_removed_print(ndo, cp, ep);
	case OFPT_PORT_STATUS: /* [OF10] Section 5.4.3 */
		if (len != OF_PORT_STATUS_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		/* reason */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, "\n\t reason %s", tok2str(ofppr_str, "invalid (0x%02x)", *cp)));
		cp += 1;
		/* pad */
		ND_TCHECK2(*cp, 7);
		cp += 7;
		/* desc */
		return of10_phy_ports_print(ndo, cp, ep, OF_PHY_PORT_LEN);

	/* OpenFlow header, fixed-size message body and n * fixed-size data units. */
	case OFPT_FEATURES_REPLY:
		if (len < OF_SWITCH_FEATURES_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_features_reply_print(ndo, cp, ep, len);

	/* OpenFlow header and variable-size data. */
	case OFPT_HELLO: /* [OF10] Section 5.5.1 */
	case OFPT_ECHO_REQUEST: /* [OF10] Section 5.5.2 */
	case OFPT_ECHO_REPLY: /* [OF10] Section 5.5.3 */
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_data_print(ndo, cp, ep, len - OF_HEADER_LEN);

	/* OpenFlow header, fixed-size message body and variable-size data. */
	case OFPT_ERROR:
		if (len < OF_ERROR_MSG_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_error_print(ndo, cp, ep, len);
	case OFPT_VENDOR:
	  /* [OF10] Section 5.5.4 */
		if (len < OF_VENDOR_HEADER_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_vendor_message_print(ndo, cp, ep, len - OF_HEADER_LEN);
	case OFPT_PACKET_IN:
		/* 2 mock octets count in OF_PACKET_IN_LEN but not in len */
		if (len < OF_PACKET_IN_LEN - 2)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_packet_in_print(ndo, cp, ep, len);

	/* a. OpenFlow header. */
	/* b. OpenFlow header and one of the fixed-size message bodies. */
	/* c. OpenFlow header, fixed-size message body and variable-size data. */
	case OFPT_STATS_REQUEST:
		if (len < OF_STATS_REQUEST_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_stats_request_print(ndo, cp, ep, len);

	/* a. OpenFlow header and fixed-size message body. */
	/* b. OpenFlow header and n * fixed-size data units. */
	/* c. OpenFlow header and n * variable-size data units. */
	/* d. OpenFlow header, fixed-size message body and variable-size data. */
	case OFPT_STATS_REPLY:
		if (len < OF_STATS_REPLY_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_stats_reply_print(ndo, cp, ep, len);

	/* OpenFlow header and n * variable-size data units and variable-size data. */
	case OFPT_PACKET_OUT:
		if (len < OF_PACKET_OUT_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_packet_out_print(ndo, cp, ep, len);

	/* OpenFlow header, fixed-size message body and n * variable-size data units. */
	case OFPT_FLOW_MOD:
		if (len < OF_FLOW_MOD_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		return of10_flow_mod_print(ndo, cp, ep, len);

	/* OpenFlow header, fixed-size message body and n * variable-size data units. */
	case OFPT_QUEUE_GET_CONFIG_REPLY: /* [OF10] Section 5.3.4 */
		if (len < OF_QUEUE_GET_CONFIG_REPLY_LEN)
			goto invalid;
		if (ndo->ndo_vflag < 1)
			goto next_message;
		/* port */
		ND_TCHECK2(*cp, 2);
		ND_PRINT((ndo, "\n\t port_no %s", tok2str(ofpp_str, "%u", EXTRACT_16BITS(cp))));
		cp += 2;
		/* pad */
		ND_TCHECK2(*cp, 6);
		cp += 6;
		/* queues */
		return of10_queues_print(ndo, cp, ep, len - OF_QUEUE_GET_CONFIG_REPLY_LEN);
	} /* switch (type) */
	goto next_message;

invalid: /* skip the message body */
	ND_PRINT((ndo, "%s", istr));
next_message:
	ND_TCHECK2(*cp0, len0 - OF_HEADER_LEN);
	return cp0 + len0 - OF_HEADER_LEN;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}