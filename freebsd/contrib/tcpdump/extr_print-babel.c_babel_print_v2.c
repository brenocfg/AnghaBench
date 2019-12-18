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
typedef  int u_short ;
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_7__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 void* EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ICHECK (int,int) ; 
#define  MESSAGE_ACK 142 
#define  MESSAGE_ACK_REQ 141 
#define  MESSAGE_HELLO 140 
#define  MESSAGE_HMAC 139 
#define  MESSAGE_IHU 138 
#define  MESSAGE_MH_REQUEST 137 
#define  MESSAGE_MH_REQUEST_SRC_SPECIFIC 136 
#define  MESSAGE_NH 135 
 int MESSAGE_PAD1 ; 
#define  MESSAGE_PADN 134 
#define  MESSAGE_REQUEST 133 
#define  MESSAGE_REQUEST_SRC_SPECIFIC 132 
#define  MESSAGE_ROUTER_ID 131 
#define  MESSAGE_TSPC 130 
#define  MESSAGE_UPDATE 129 
#define  MESSAGE_UPDATE_SRC_SPECIFIC 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  format_address (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  format_id (int const*) ; 
 int /*<<< orphan*/  format_interval (unsigned short) ; 
 int /*<<< orphan*/  format_interval_update (int) ; 
 char* format_prefix (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int network_address (int const,int const*,int,int*) ; 
 int network_prefix (int const,int const,int const,int const*,int*,int,int*) ; 
 int /*<<< orphan*/  subtlvs_print (TYPE_1__*,int const*,int const*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
babel_print_v2(netdissect_options *ndo,
               const u_char *cp, u_int length)
{
    u_int i;
    u_short bodylen;
    u_char v4_prefix[16] =
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0, 0, 0, 0 };
    u_char v6_prefix[16] = {0};

    ND_TCHECK2(*cp, 4);
    if (length < 4)
        goto invalid;
    bodylen = EXTRACT_16BITS(cp + 2);
    ND_PRINT((ndo, " (%u)", bodylen));

    /* Process the TLVs in the body */
    i = 0;
    while(i < bodylen) {
        const u_char *message;
        u_int type, len;

        message = cp + 4 + i;

        ND_TCHECK2(*message, 1);
        if((type = message[0]) == MESSAGE_PAD1) {
            ND_PRINT((ndo, ndo->ndo_vflag ? "\n\tPad 1" : " pad1"));
            i += 1;
            continue;
        }

        ND_TCHECK2(*message, 2);
        ICHECK(i, 2);
        len = message[1];

        ND_TCHECK2(*message, 2 + len);
        ICHECK(i, 2 + len);

        switch(type) {
        case MESSAGE_PADN: {
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " padN"));
            else
                ND_PRINT((ndo, "\n\tPad %d", len + 2));
        }
            break;

        case MESSAGE_ACK_REQ: {
            u_short nonce, interval;
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " ack-req"));
            else {
                ND_PRINT((ndo, "\n\tAcknowledgment Request "));
                if(len < 6) goto invalid;
                nonce = EXTRACT_16BITS(message + 4);
                interval = EXTRACT_16BITS(message + 6);
                ND_PRINT((ndo, "%04x %s", nonce, format_interval(interval)));
            }
        }
            break;

        case MESSAGE_ACK: {
            u_short nonce;
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " ack"));
            else {
                ND_PRINT((ndo, "\n\tAcknowledgment "));
                if(len < 2) goto invalid;
                nonce = EXTRACT_16BITS(message + 2);
                ND_PRINT((ndo, "%04x", nonce));
            }
        }
            break;

        case MESSAGE_HELLO:  {
            u_short seqno, interval;
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " hello"));
            else {
                ND_PRINT((ndo, "\n\tHello "));
                if(len < 6) goto invalid;
                seqno = EXTRACT_16BITS(message + 4);
                interval = EXTRACT_16BITS(message + 6);
                ND_PRINT((ndo, "seqno %u interval %s", seqno, format_interval(interval)));
                /* Extra data. */
                if(len > 6)
                    subtlvs_print(ndo, message + 8, message + 2 + len, type);
            }
        }
            break;

        case MESSAGE_IHU: {
            unsigned short txcost, interval;
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " ihu"));
            else {
                u_char address[16];
                int rc;
                ND_PRINT((ndo, "\n\tIHU "));
                if(len < 6) goto invalid;
                txcost = EXTRACT_16BITS(message + 4);
                interval = EXTRACT_16BITS(message + 6);
                rc = network_address(message[2], message + 8, len - 6, address);
                if(rc < 0) { ND_PRINT((ndo, "%s", tstr)); break; }
                ND_PRINT((ndo, "%s txcost %u interval %s",
                       format_address(ndo, address), txcost, format_interval(interval)));
                /* Extra data. */
                if((u_int)rc < len - 6)
                    subtlvs_print(ndo, message + 8 + rc, message + 2 + len,
                                  type);
            }
        }
            break;

        case MESSAGE_ROUTER_ID: {
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " router-id"));
            else {
                ND_PRINT((ndo, "\n\tRouter Id"));
                if(len < 10) goto invalid;
                ND_PRINT((ndo, " %s", format_id(message + 4)));
            }
        }
            break;

        case MESSAGE_NH: {
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " nh"));
            else {
                int rc;
                u_char nh[16];
                ND_PRINT((ndo, "\n\tNext Hop"));
                if(len < 2) goto invalid;
                rc = network_address(message[2], message + 4, len - 2, nh);
                if(rc < 0) goto invalid;
                ND_PRINT((ndo, " %s", format_address(ndo, nh)));
            }
        }
            break;

        case MESSAGE_UPDATE: {
            if (!ndo->ndo_vflag) {
                ND_PRINT((ndo, " update"));
                if(len < 1)
                    ND_PRINT((ndo, "/truncated"));
                else
                    ND_PRINT((ndo, "%s%s%s",
                           (message[3] & 0x80) ? "/prefix": "",
                           (message[3] & 0x40) ? "/id" : "",
                           (message[3] & 0x3f) ? "/unknown" : ""));
            } else {
                u_short interval, seqno, metric;
                u_char plen;
                int rc;
                u_char prefix[16];
                ND_PRINT((ndo, "\n\tUpdate"));
                if(len < 10) goto invalid;
                plen = message[4] + (message[2] == 1 ? 96 : 0);
                rc = network_prefix(message[2], message[4], message[5],
                                    message + 12,
                                    message[2] == 1 ? v4_prefix : v6_prefix,
                                    len - 10, prefix);
                if(rc < 0) goto invalid;
                interval = EXTRACT_16BITS(message + 6);
                seqno = EXTRACT_16BITS(message + 8);
                metric = EXTRACT_16BITS(message + 10);
                ND_PRINT((ndo, "%s%s%s %s metric %u seqno %u interval %s",
                       (message[3] & 0x80) ? "/prefix": "",
                       (message[3] & 0x40) ? "/id" : "",
                       (message[3] & 0x3f) ? "/unknown" : "",
                       format_prefix(ndo, prefix, plen),
                       metric, seqno, format_interval_update(interval)));
                if(message[3] & 0x80) {
                    if(message[2] == 1)
                        memcpy(v4_prefix, prefix, 16);
                    else
                        memcpy(v6_prefix, prefix, 16);
                }
                /* extra data? */
                if((u_int)rc < len - 10)
                    subtlvs_print(ndo, message + 12 + rc, message + 2 + len, type);
            }
        }
            break;

        case MESSAGE_REQUEST: {
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " request"));
            else {
                int rc;
                u_char prefix[16], plen;
                ND_PRINT((ndo, "\n\tRequest "));
                if(len < 2) goto invalid;
                plen = message[3] + (message[2] == 1 ? 96 : 0);
                rc = network_prefix(message[2], message[3], 0,
                                    message + 4, NULL, len - 2, prefix);
                if(rc < 0) goto invalid;
                ND_PRINT((ndo, "for %s",
                       message[2] == 0 ? "any" : format_prefix(ndo, prefix, plen)));
            }
        }
            break;

        case MESSAGE_MH_REQUEST : {
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " mh-request"));
            else {
                int rc;
                u_short seqno;
                u_char prefix[16], plen;
                ND_PRINT((ndo, "\n\tMH-Request "));
                if(len < 14) goto invalid;
                seqno = EXTRACT_16BITS(message + 4);
                rc = network_prefix(message[2], message[3], 0,
                                    message + 16, NULL, len - 14, prefix);
                if(rc < 0) goto invalid;
                plen = message[3] + (message[2] == 1 ? 96 : 0);
                ND_PRINT((ndo, "(%u hops) for %s seqno %u id %s",
                       message[6], format_prefix(ndo, prefix, plen),
                       seqno, format_id(message + 8)));
            }
        }
            break;
        case MESSAGE_TSPC :
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " tspc"));
            else {
                ND_PRINT((ndo, "\n\tTS/PC "));
                if(len < 6) goto invalid;
                ND_PRINT((ndo, "timestamp %u packetcounter %u", EXTRACT_32BITS (message + 4),
                       EXTRACT_16BITS(message + 2)));
            }
            break;
        case MESSAGE_HMAC : {
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " hmac"));
            else {
                unsigned j;
                ND_PRINT((ndo, "\n\tHMAC "));
                if(len < 18) goto invalid;
                ND_PRINT((ndo, "key-id %u digest-%u ", EXTRACT_16BITS(message + 2), len - 2));
                for (j = 0; j < len - 2; j++)
                    ND_PRINT((ndo, "%02X", message[4 + j]));
            }
        }
            break;

        case MESSAGE_UPDATE_SRC_SPECIFIC : {
            if(!ndo->ndo_vflag) {
                ND_PRINT((ndo, " ss-update"));
            } else {
                u_char prefix[16], src_prefix[16];
                u_short interval, seqno, metric;
                u_char ae, plen, src_plen, omitted;
                int rc;
                int parsed_len = 10;
                ND_PRINT((ndo, "\n\tSS-Update"));
                if(len < 10) goto invalid;
                ae = message[2];
                src_plen = message[3];
                plen = message[4];
                omitted = message[5];
                interval = EXTRACT_16BITS(message + 6);
                seqno = EXTRACT_16BITS(message + 8);
                metric = EXTRACT_16BITS(message + 10);
                rc = network_prefix(ae, plen, omitted, message + 2 + parsed_len,
                                    ae == 1 ? v4_prefix : v6_prefix,
                                    len - parsed_len, prefix);
                if(rc < 0) goto invalid;
                if(ae == 1)
                    plen += 96;
                parsed_len += rc;
                rc = network_prefix(ae, src_plen, 0, message + 2 + parsed_len,
                                    NULL, len - parsed_len, src_prefix);
                if(rc < 0) goto invalid;
                if(ae == 1)
                    src_plen += 96;
                parsed_len += rc;

                ND_PRINT((ndo, " %s from", format_prefix(ndo, prefix, plen)));
                ND_PRINT((ndo, " %s metric %u seqno %u interval %s",
                          format_prefix(ndo, src_prefix, src_plen),
                          metric, seqno, format_interval_update(interval)));
                /* extra data? */
                if((u_int)parsed_len < len)
                    subtlvs_print(ndo, message + 2 + parsed_len,
                                  message + 2 + len, type);
            }
        }
            break;

        case MESSAGE_REQUEST_SRC_SPECIFIC : {
            if(!ndo->ndo_vflag)
                ND_PRINT((ndo, " ss-request"));
            else {
                int rc, parsed_len = 3;
                u_char ae, plen, src_plen, prefix[16], src_prefix[16];
                ND_PRINT((ndo, "\n\tSS-Request "));
                if(len < 3) goto invalid;
                ae = message[2];
                plen = message[3];
                src_plen = message[4];
                rc = network_prefix(ae, plen, 0, message + 2 + parsed_len,
                                    NULL, len - parsed_len, prefix);
                if(rc < 0) goto invalid;
                if(ae == 1)
                    plen += 96;
                parsed_len += rc;
                rc = network_prefix(ae, src_plen, 0, message + 2 + parsed_len,
                                    NULL, len - parsed_len, src_prefix);
                if(rc < 0) goto invalid;
                if(ae == 1)
                    src_plen += 96;
                parsed_len += rc;
                if(ae == 0) {
                    ND_PRINT((ndo, "for any"));
                } else {
                    ND_PRINT((ndo, "for (%s, ", format_prefix(ndo, prefix, plen)));
                    ND_PRINT((ndo, "%s)", format_prefix(ndo, src_prefix, src_plen)));
                }
            }
        }
            break;

        case MESSAGE_MH_REQUEST_SRC_SPECIFIC : {
            if(!ndo->ndo_vflag)
                ND_PRINT((ndo, " ss-mh-request"));
            else {
                int rc, parsed_len = 14;
                u_short seqno;
                u_char ae, plen, src_plen, prefix[16], src_prefix[16], hopc;
                const u_char *router_id = NULL;
                ND_PRINT((ndo, "\n\tSS-MH-Request "));
                if(len < 14) goto invalid;
                ae = message[2];
                plen = message[3];
                seqno = EXTRACT_16BITS(message + 4);
                hopc = message[6];
                src_plen = message[7];
                router_id = message + 8;
                rc = network_prefix(ae, plen, 0, message + 2 + parsed_len,
                                    NULL, len - parsed_len, prefix);
                if(rc < 0) goto invalid;
                if(ae == 1)
                    plen += 96;
                parsed_len += rc;
                rc = network_prefix(ae, src_plen, 0, message + 2 + parsed_len,
                                    NULL, len - parsed_len, src_prefix);
                if(rc < 0) goto invalid;
                if(ae == 1)
                    src_plen += 96;
                ND_PRINT((ndo, "(%u hops) for (%s, ",
                          hopc, format_prefix(ndo, prefix, plen)));
                ND_PRINT((ndo, "%s) seqno %u id %s",
                          format_prefix(ndo, src_prefix, src_plen),
                          seqno, format_id(router_id)));
            }
        }
            break;

        default:
            if (!ndo->ndo_vflag)
                ND_PRINT((ndo, " unknown"));
            else
                ND_PRINT((ndo, "\n\tUnknown message type %d", type));
        }
        i += len + 2;
    }
    return;

 trunc:
    ND_PRINT((ndo, " %s", tstr));
    return;

 invalid:
    ND_PRINT((ndo, "%s", istr));
    return;
}