#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lwapp_transport_header {int version; int /*<<< orphan*/  frag_id; int /*<<< orphan*/  length; } ;
struct lwapp_control_header {int msg_type; int /*<<< orphan*/  session_id; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ LWAPP_EXTRACT_CONTROL_BIT (int) ; 
 int /*<<< orphan*/  LWAPP_EXTRACT_RID (int) ; 
 scalar_t__ LWAPP_EXTRACT_VERSION (int) ; 
#define  LWAPP_MSGTYPE_CHANGE_STATE_EVENT_REQUEST 158 
#define  LWAPP_MSGTYPE_CHANGE_STATE_EVENT_RESPONSE 157 
#define  LWAPP_MSGTYPE_CLEAR_CONFIG_INDICATION 156 
#define  LWAPP_MSGTYPE_CONFIGURE_REQUEST 155 
#define  LWAPP_MSGTYPE_CONFIGURE_RESPONSE 154 
#define  LWAPP_MSGTYPE_CONF_UPDATE_REQUEST 153 
#define  LWAPP_MSGTYPE_CONF_UPDATE_RESPONSE 152 
#define  LWAPP_MSGTYPE_DATA_TRANSFER_REQUEST 151 
#define  LWAPP_MSGTYPE_DATA_TRANSFER_RESPONSE 150 
#define  LWAPP_MSGTYPE_DISCOVERY_REQUEST 149 
#define  LWAPP_MSGTYPE_DISCOVERY_RESPONSE 148 
#define  LWAPP_MSGTYPE_ECHO_REQUEST 147 
#define  LWAPP_MSGTYPE_ECHO_RESPONSE 146 
#define  LWAPP_MSGTYPE_IMAGE_DATA_REQUEST 145 
#define  LWAPP_MSGTYPE_IMAGE_DATA_RESPONSE 144 
#define  LWAPP_MSGTYPE_JOIN_ACK 143 
#define  LWAPP_MSGTYPE_JOIN_CONFIRM 142 
#define  LWAPP_MSGTYPE_JOIN_REQUEST 141 
#define  LWAPP_MSGTYPE_JOIN_RESPONSE 140 
#define  LWAPP_MSGTYPE_KEY_UPDATE_REQUEST 139 
#define  LWAPP_MSGTYPE_KEY_UPDATE_RESPONSE 138 
#define  LWAPP_MSGTYPE_MOBILE_CONFIG_REQUEST 137 
#define  LWAPP_MSGTYPE_MOBILE_CONFIG_RESPONSE 136 
#define  LWAPP_MSGTYPE_PRIMARY_DISCOVERY_REQUEST 135 
#define  LWAPP_MSGTYPE_PRIMARY_DISCOVERY_RESPONSE 134 
#define  LWAPP_MSGTYPE_RESET_REQUEST 133 
#define  LWAPP_MSGTYPE_RESET_RESPONSE 132 
#define  LWAPP_MSGTYPE_WLAN_CONFIG_REQUEST 131 
#define  LWAPP_MSGTYPE_WLAN_CONFIG_RESPONSE 130 
#define  LWAPP_MSGTYPE_WTP_EVENT_REQUEST 129 
#define  LWAPP_MSGTYPE_WTP_EVENT_RESPONSE 128 
 scalar_t__ LWAPP_VERSION ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct lwapp_transport_header const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  etheraddr_string (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lwapp_header_bits_values ; 
 int /*<<< orphan*/  lwapp_msg_type_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

void
lwapp_control_print(netdissect_options *ndo,
                    const u_char *pptr, u_int len, int has_ap_ident)
{
    const struct lwapp_transport_header *lwapp_trans_header;
    const struct lwapp_control_header *lwapp_control_header;
    const u_char *tptr;
    int  tlen;
    int  msg_tlen;

    tptr=pptr;

    if (has_ap_ident) {
        /* check if enough bytes for AP identity */
        ND_TCHECK2(*tptr, 6);
        lwapp_trans_header = (const struct lwapp_transport_header *)(pptr+6);
    } else {
        lwapp_trans_header = (const struct lwapp_transport_header *)pptr;
    }
    ND_TCHECK(*lwapp_trans_header);

    /*
     * Sanity checking of the header.
     */
    if (LWAPP_EXTRACT_VERSION(lwapp_trans_header->version) != LWAPP_VERSION) {
	ND_PRINT((ndo, "LWAPP version %u packet not supported",
               LWAPP_EXTRACT_VERSION(lwapp_trans_header->version)));
	return;
    }

    /* non-verbose */
    if (ndo->ndo_vflag < 1) {
        ND_PRINT((ndo, "LWAPPv%u, %s frame, Flags [%s], length %u",
               LWAPP_EXTRACT_VERSION(lwapp_trans_header->version),
               LWAPP_EXTRACT_CONTROL_BIT(lwapp_trans_header->version) ? "Control" : "Data",
               bittok2str(lwapp_header_bits_values,"none",(lwapp_trans_header->version)&0x07),
               len));
        return;
    }

    /* ok they seem to want to know everything - lets fully decode it */
    tlen=EXTRACT_16BITS(lwapp_trans_header->length);

    ND_PRINT((ndo, "LWAPPv%u, %s frame, Radio-id %u, Flags [%s], Frag-id %u, length %u",
           LWAPP_EXTRACT_VERSION(lwapp_trans_header->version),
           LWAPP_EXTRACT_CONTROL_BIT(lwapp_trans_header->version) ? "Control" : "Data",
           LWAPP_EXTRACT_RID(lwapp_trans_header->version),
           bittok2str(lwapp_header_bits_values,"none",(lwapp_trans_header->version)&0x07),
	   lwapp_trans_header->frag_id,
	   tlen));

    if (has_ap_ident) {
        ND_PRINT((ndo, "\n\tAP identity: %s", etheraddr_string(ndo, tptr)));
        tptr+=sizeof(const struct lwapp_transport_header)+6;
    } else {
        tptr+=sizeof(const struct lwapp_transport_header);
    }

    while(tlen>0) {

        /* did we capture enough for fully decoding the object header ? */
        ND_TCHECK2(*tptr, sizeof(struct lwapp_control_header));

        lwapp_control_header = (const struct lwapp_control_header *)tptr;
	msg_tlen = EXTRACT_16BITS(lwapp_control_header->len);

	/* print message header */
        ND_PRINT((ndo, "\n\t  Msg type: %s (%u), Seqnum: %u, Msg len: %d, Session: 0x%08x",
               tok2str(lwapp_msg_type_values,"Unknown",lwapp_control_header->msg_type),
               lwapp_control_header->msg_type,
               lwapp_control_header->seq_num,
               msg_tlen,
               EXTRACT_32BITS(lwapp_control_header->session_id)));

        /* did we capture enough for fully decoding the message */
        ND_TCHECK2(*tptr, msg_tlen);

	/* XXX - Decode sub messages for each message */
        switch(lwapp_control_header->msg_type) {
        case LWAPP_MSGTYPE_DISCOVERY_REQUEST:
        case LWAPP_MSGTYPE_DISCOVERY_RESPONSE:
        case LWAPP_MSGTYPE_JOIN_REQUEST:
        case LWAPP_MSGTYPE_JOIN_RESPONSE:
        case LWAPP_MSGTYPE_JOIN_ACK:
        case LWAPP_MSGTYPE_JOIN_CONFIRM:
        case LWAPP_MSGTYPE_CONFIGURE_REQUEST:
        case LWAPP_MSGTYPE_CONFIGURE_RESPONSE:
        case LWAPP_MSGTYPE_CONF_UPDATE_REQUEST:
        case LWAPP_MSGTYPE_CONF_UPDATE_RESPONSE:
        case LWAPP_MSGTYPE_WTP_EVENT_REQUEST:
        case LWAPP_MSGTYPE_WTP_EVENT_RESPONSE:
        case LWAPP_MSGTYPE_CHANGE_STATE_EVENT_REQUEST:
        case LWAPP_MSGTYPE_CHANGE_STATE_EVENT_RESPONSE:
        case LWAPP_MSGTYPE_ECHO_REQUEST:
        case LWAPP_MSGTYPE_ECHO_RESPONSE:
        case LWAPP_MSGTYPE_IMAGE_DATA_REQUEST:
        case LWAPP_MSGTYPE_IMAGE_DATA_RESPONSE:
        case LWAPP_MSGTYPE_RESET_REQUEST:
        case LWAPP_MSGTYPE_RESET_RESPONSE:
        case LWAPP_MSGTYPE_KEY_UPDATE_REQUEST:
        case LWAPP_MSGTYPE_KEY_UPDATE_RESPONSE:
        case LWAPP_MSGTYPE_PRIMARY_DISCOVERY_REQUEST:
        case LWAPP_MSGTYPE_PRIMARY_DISCOVERY_RESPONSE:
        case LWAPP_MSGTYPE_DATA_TRANSFER_REQUEST:
        case LWAPP_MSGTYPE_DATA_TRANSFER_RESPONSE:
        case LWAPP_MSGTYPE_CLEAR_CONFIG_INDICATION:
        case LWAPP_MSGTYPE_WLAN_CONFIG_REQUEST:
        case LWAPP_MSGTYPE_WLAN_CONFIG_RESPONSE:
        case LWAPP_MSGTYPE_MOBILE_CONFIG_REQUEST:
        case LWAPP_MSGTYPE_MOBILE_CONFIG_RESPONSE:
        default:
            break;
        }

        tptr += sizeof(struct lwapp_control_header) + msg_tlen;
        tlen -= sizeof(struct lwapp_control_header) + msg_tlen;
    }
    return;

 trunc:
    ND_PRINT((ndo, "\n\t\t packet exceeded snapshot"));
}