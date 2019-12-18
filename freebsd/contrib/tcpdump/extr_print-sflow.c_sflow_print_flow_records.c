#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sflow_flow_record_t {int /*<<< orphan*/  length; int /*<<< orphan*/  format; } ;
struct TYPE_8__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct sflow_flow_record_t const) ; 
#define  SFLOW_FLOW_ETHERNET_FRAME 143 
#define  SFLOW_FLOW_EXTENDED_GATEWAY_DATA 142 
#define  SFLOW_FLOW_EXTENDED_MPLS_DATA 141 
#define  SFLOW_FLOW_EXTENDED_MPLS_FEC 140 
#define  SFLOW_FLOW_EXTENDED_MPLS_LVP_FEC 139 
#define  SFLOW_FLOW_EXTENDED_MPLS_TUNNEL 138 
#define  SFLOW_FLOW_EXTENDED_MPLS_VC 137 
#define  SFLOW_FLOW_EXTENDED_NAT_DATA 136 
#define  SFLOW_FLOW_EXTENDED_ROUTER_DATA 135 
#define  SFLOW_FLOW_EXTENDED_SWITCH_DATA 134 
#define  SFLOW_FLOW_EXTENDED_URL_DATA 133 
#define  SFLOW_FLOW_EXTENDED_USER_DATA 132 
#define  SFLOW_FLOW_EXTENDED_VLAN_TUNNEL 131 
#define  SFLOW_FLOW_IPV4_DATA 130 
#define  SFLOW_FLOW_IPV6_DATA 129 
#define  SFLOW_FLOW_RAW_PACKET 128 
 int /*<<< orphan*/  print_sflow_ethernet_frame (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_extended_switch_data (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_raw_packet (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int /*<<< orphan*/  const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sflow_flow_type_values ; 
 char* tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
sflow_print_flow_records(netdissect_options *ndo,
                         const u_char *pointer, u_int len, u_int records)
{
    u_int nrecords;
    const u_char *tptr;
    u_int tlen;
    u_int flow_type;
    u_int enterprise;
    u_int flow_len;
    const struct sflow_flow_record_t *sflow_flow_record;

    nrecords = records;
    tptr = pointer;
    tlen = len;

    while (nrecords > 0) {
	/* do we have the "header?" */
	if (tlen < sizeof(struct sflow_flow_record_t))
	    return 1;

	sflow_flow_record = (const struct sflow_flow_record_t *)tptr;
	ND_TCHECK(*sflow_flow_record);

	/* so, the funky encoding means we cannot blythly mask-off
	   bits, we must also check the enterprise. */

	enterprise = EXTRACT_32BITS(sflow_flow_record->format);
	flow_type = enterprise & 0x0FFF;
	enterprise = enterprise >> 12;
	flow_len  = EXTRACT_32BITS(sflow_flow_record->length);
	ND_PRINT((ndo, "\n\t    enterprise %u %s (%u) length %u",
	       enterprise,
	       (enterprise == 0) ? tok2str(sflow_flow_type_values,"Unknown",flow_type) : "Unknown",
	       flow_type,
	       flow_len));

	tptr += sizeof(struct sflow_flow_record_t);
	tlen -= sizeof(struct sflow_flow_record_t);

	if (tlen < flow_len)
	    return 1;

	if (enterprise == 0) {
	    switch (flow_type) {
	    case SFLOW_FLOW_RAW_PACKET:
		if (print_sflow_raw_packet(ndo, tptr, tlen))
		    return 1;
		break;
	    case SFLOW_FLOW_EXTENDED_SWITCH_DATA:
		if (print_sflow_extended_switch_data(ndo, tptr, tlen))
		    return 1;
		break;
	    case SFLOW_FLOW_ETHERNET_FRAME:
		if (print_sflow_ethernet_frame(ndo, tptr, tlen))
		    return 1;
		break;
		/* FIXME these need a decoder */
	    case SFLOW_FLOW_IPV4_DATA:
	    case SFLOW_FLOW_IPV6_DATA:
	    case SFLOW_FLOW_EXTENDED_ROUTER_DATA:
	    case SFLOW_FLOW_EXTENDED_GATEWAY_DATA:
	    case SFLOW_FLOW_EXTENDED_USER_DATA:
	    case SFLOW_FLOW_EXTENDED_URL_DATA:
	    case SFLOW_FLOW_EXTENDED_MPLS_DATA:
	    case SFLOW_FLOW_EXTENDED_NAT_DATA:
	    case SFLOW_FLOW_EXTENDED_MPLS_TUNNEL:
	    case SFLOW_FLOW_EXTENDED_MPLS_VC:
	    case SFLOW_FLOW_EXTENDED_MPLS_FEC:
	    case SFLOW_FLOW_EXTENDED_MPLS_LVP_FEC:
	    case SFLOW_FLOW_EXTENDED_VLAN_TUNNEL:
		break;
	    default:
		if (ndo->ndo_vflag <= 1)
		    print_unknown_data(ndo, tptr, "\n\t\t", flow_len);
		break;
	    }
	}
	tptr += flow_len;
	tlen -= flow_len;
	nrecords--;

    }

    return 0;

trunc:
    return 1;
}