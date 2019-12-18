#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct lspping_tlv_targetfec_subtlv_rsvp_ipv6_t {int /*<<< orphan*/  extended_tunnel_id; int /*<<< orphan*/ * tunnel_id; int /*<<< orphan*/ * lsp_id; int /*<<< orphan*/  tunnel_sender; int /*<<< orphan*/  tunnel_endpoint; } ;
struct lspping_tlv_targetfec_subtlv_rsvp_ipv4_t {int /*<<< orphan*/  extended_tunnel_id; int /*<<< orphan*/ * tunnel_id; int /*<<< orphan*/ * lsp_id; int /*<<< orphan*/  tunnel_sender; int /*<<< orphan*/  tunnel_endpoint; } ;
struct lspping_tlv_targetfec_subtlv_ldp_ipv6_t {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  prefix; } ;
struct lspping_tlv_targetfec_subtlv_ldp_ipv4_t {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  prefix; } ;
struct lspping_tlv_targetfec_subtlv_l3vpn_ipv6_t {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  prefix; int /*<<< orphan*/  rd; } ;
struct lspping_tlv_targetfec_subtlv_l3vpn_ipv4_t {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  prefix; int /*<<< orphan*/  rd; } ;
struct lspping_tlv_targetfec_subtlv_l2vpn_endpt_t {int /*<<< orphan*/ * encapsulation; int /*<<< orphan*/ * receiver_ve_id; int /*<<< orphan*/ * sender_ve_id; int /*<<< orphan*/  rd; } ;
struct lspping_tlv_targetfec_subtlv_fec_128_pw_old {int /*<<< orphan*/ * pw_type; int /*<<< orphan*/  const* pw_id; int /*<<< orphan*/  remote_pe_address; } ;
struct lspping_tlv_targetfec_subtlv_fec_128_pw {int /*<<< orphan*/ * pw_type; int /*<<< orphan*/  const* pw_id; int /*<<< orphan*/  remote_pe_address; int /*<<< orphan*/  sender_pe_address; } ;
struct lspping_tlv_targetfec_subtlv_bgp_ipv6_t {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  prefix; } ;
struct lspping_tlv_targetfec_subtlv_bgp_ipv4_t {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  prefix; } ;
struct lspping_tlv_header {int /*<<< orphan*/ * length; int /*<<< orphan*/ * type; } ;
struct lspping_tlv_downstream_map_t {int address_type; int /*<<< orphan*/ * mtu; } ;
struct lspping_tlv_downstream_map_ipv6_unmb_t {int /*<<< orphan*/  const* downstream_interface; int /*<<< orphan*/  downstream_ip; } ;
struct lspping_tlv_downstream_map_ipv6_t {int /*<<< orphan*/  downstream_interface; int /*<<< orphan*/  downstream_ip; } ;
struct lspping_tlv_downstream_map_ipv4_unmb_t {int /*<<< orphan*/  const* downstream_interface; int /*<<< orphan*/  downstream_ip; } ;
struct lspping_tlv_downstream_map_ipv4_t {int /*<<< orphan*/  downstream_interface; int /*<<< orphan*/  downstream_ip; } ;
struct lspping_tlv_downstream_map_info_t {int dummy; } ;
struct lspping_common_header {int msg_type; int reply_mode; int return_code; int /*<<< orphan*/  const* ts_rcvd_usec; int /*<<< orphan*/  const* ts_rcvd_sec; int /*<<< orphan*/  const* ts_sent_usec; int /*<<< orphan*/  const* ts_sent_sec; int /*<<< orphan*/  const* seq_number; int /*<<< orphan*/  const* sender_handle; int /*<<< orphan*/  return_subcode; int /*<<< orphan*/ * version; } ;
struct TYPE_9__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 void* EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int FALSE ; 
#define  LSPPING_AFI_IPV4 149 
#define  LSPPING_AFI_IPV4_UNMB 148 
#define  LSPPING_AFI_IPV6 147 
#define  LSPPING_AFI_IPV6_UNMB 146 
#define  LSPPING_TLV_BFD_DISCRIMINATOR 145 
 int LSPPING_TLV_BFD_DISCRIMINATOR_LEN ; 
#define  LSPPING_TLV_DOWNSTREAM_MAPPING 144 
#define  LSPPING_TLV_ERROR_CODE 143 
#define  LSPPING_TLV_PAD 142 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_BGP_IPV4 141 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_BGP_IPV6 140 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_FEC_128_PW 139 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_FEC_128_PW_OLD 138 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_L2VPN_ENDPT 137 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_L3VPN_IPV4 136 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_L3VPN_IPV6 135 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_LDP_IPV4 134 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_LDP_IPV6 133 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_RSVP_IPV4 132 
#define  LSPPING_TLV_TARGETFEC_SUBTLV_RSVP_IPV6 131 
#define  LSPPING_TLV_TARGET_FEC_STACK 130 
#define  LSPPING_TLV_VENDOR_ENTERPRISE 129 
 int LSPPING_TLV_VENDOR_ENTERPRISE_LEN ; 
#define  LSPPING_TLV_VENDOR_PRIVATE 128 
 scalar_t__ LSPPING_VERSION ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct lspping_common_header const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  bgp_vpn_rd_print (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6addr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lspping_msg_type_values ; 
 int /*<<< orphan*/  lspping_reply_mode_values ; 
 int /*<<< orphan*/  lspping_return_code_values ; 
 int /*<<< orphan*/  lspping_tlv_downstream_addr_values ; 
 int /*<<< orphan*/  lspping_tlv_values ; 
 int /*<<< orphan*/  lspping_tlvtargetfec_subtlv_values ; 
 int /*<<< orphan*/  mpls_pw_types_values ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  smi_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ts_print (TYPE_1__*,struct timeval*) ; 

void
lspping_print(netdissect_options *ndo,
              register const u_char *pptr, register u_int len)
{
    const struct lspping_common_header *lspping_com_header;
    const struct lspping_tlv_header *lspping_tlv_header;
    const struct lspping_tlv_header *lspping_subtlv_header;
    const u_char *tptr,*tlv_tptr,*subtlv_tptr;
    u_int tlen,lspping_tlv_len,lspping_tlv_type,tlv_tlen;
    int tlv_hexdump,subtlv_hexdump;
    u_int lspping_subtlv_len,lspping_subtlv_type;
    struct timeval timestamp;

    union {
        const struct lspping_tlv_downstream_map_t *lspping_tlv_downstream_map;
        const struct lspping_tlv_downstream_map_ipv4_t *lspping_tlv_downstream_map_ipv4;
        const struct lspping_tlv_downstream_map_ipv4_unmb_t *lspping_tlv_downstream_map_ipv4_unmb;
        const struct lspping_tlv_downstream_map_ipv6_t *lspping_tlv_downstream_map_ipv6;
        const struct lspping_tlv_downstream_map_ipv6_unmb_t *lspping_tlv_downstream_map_ipv6_unmb;
        const struct lspping_tlv_downstream_map_info_t  *lspping_tlv_downstream_map_info;
    } tlv_ptr;

    union {
        const struct lspping_tlv_targetfec_subtlv_ldp_ipv4_t *lspping_tlv_targetfec_subtlv_ldp_ipv4;
        const struct lspping_tlv_targetfec_subtlv_ldp_ipv6_t *lspping_tlv_targetfec_subtlv_ldp_ipv6;
        const struct lspping_tlv_targetfec_subtlv_rsvp_ipv4_t *lspping_tlv_targetfec_subtlv_rsvp_ipv4;
        const struct lspping_tlv_targetfec_subtlv_rsvp_ipv6_t *lspping_tlv_targetfec_subtlv_rsvp_ipv6;
        const struct lspping_tlv_targetfec_subtlv_l3vpn_ipv4_t *lspping_tlv_targetfec_subtlv_l3vpn_ipv4;
        const struct lspping_tlv_targetfec_subtlv_l3vpn_ipv6_t *lspping_tlv_targetfec_subtlv_l3vpn_ipv6;
        const struct lspping_tlv_targetfec_subtlv_l2vpn_endpt_t *lspping_tlv_targetfec_subtlv_l2vpn_endpt;
        const struct lspping_tlv_targetfec_subtlv_fec_128_pw_old *lspping_tlv_targetfec_subtlv_l2vpn_vcid_old;
        const struct lspping_tlv_targetfec_subtlv_fec_128_pw *lspping_tlv_targetfec_subtlv_l2vpn_vcid;
        const struct lspping_tlv_targetfec_subtlv_bgp_ipv4_t *lspping_tlv_targetfec_subtlv_bgp_ipv4;
        const struct lspping_tlv_targetfec_subtlv_bgp_ipv6_t *lspping_tlv_targetfec_subtlv_bgp_ipv6;
    } subtlv_ptr;

    tptr=pptr;
    lspping_com_header = (const struct lspping_common_header *)pptr;
    if (len < sizeof(const struct lspping_common_header))
        goto tooshort;
    ND_TCHECK(*lspping_com_header);

    /*
     * Sanity checking of the header.
     */
    if (EXTRACT_16BITS(&lspping_com_header->version[0]) != LSPPING_VERSION) {
	ND_PRINT((ndo, "LSP-PING version %u packet not supported",
               EXTRACT_16BITS(&lspping_com_header->version[0])));
	return;
    }

    /* in non-verbose mode just lets print the basic Message Type*/
    if (ndo->ndo_vflag < 1) {
        ND_PRINT((ndo, "LSP-PINGv%u, %s, seq %u, length: %u",
               EXTRACT_16BITS(&lspping_com_header->version[0]),
               tok2str(lspping_msg_type_values, "unknown (%u)",lspping_com_header->msg_type),
               EXTRACT_32BITS(lspping_com_header->seq_number),
               len));
        return;
    }

    /* ok they seem to want to know everything - lets fully decode it */

    tlen=len;

    ND_PRINT((ndo, "\n\tLSP-PINGv%u, msg-type: %s (%u), length: %u\n\t  reply-mode: %s (%u)",
           EXTRACT_16BITS(&lspping_com_header->version[0]),
           tok2str(lspping_msg_type_values, "unknown",lspping_com_header->msg_type),
           lspping_com_header->msg_type,
           len,
           tok2str(lspping_reply_mode_values, "unknown",lspping_com_header->reply_mode),
           lspping_com_header->reply_mode));

    /*
     *  the following return codes require that the subcode is attached
     *  at the end of the translated token output
     */
    if (lspping_com_header->return_code == 3 ||
        lspping_com_header->return_code == 4 ||
        lspping_com_header->return_code == 8 ||
        lspping_com_header->return_code == 10 ||
        lspping_com_header->return_code == 11 ||
        lspping_com_header->return_code == 12 )
        ND_PRINT((ndo, "\n\t  Return Code: %s %u (%u)\n\t  Return Subcode: (%u)",
               tok2str(lspping_return_code_values, "unknown",lspping_com_header->return_code),
               lspping_com_header->return_subcode,
               lspping_com_header->return_code,
               lspping_com_header->return_subcode));
    else
        ND_PRINT((ndo, "\n\t  Return Code: %s (%u)\n\t  Return Subcode: (%u)",
               tok2str(lspping_return_code_values, "unknown",lspping_com_header->return_code),
               lspping_com_header->return_code,
               lspping_com_header->return_subcode));

    ND_PRINT((ndo, "\n\t  Sender Handle: 0x%08x, Sequence: %u",
           EXTRACT_32BITS(lspping_com_header->sender_handle),
           EXTRACT_32BITS(lspping_com_header->seq_number)));

    timestamp.tv_sec=EXTRACT_32BITS(lspping_com_header->ts_sent_sec);
    timestamp.tv_usec=EXTRACT_32BITS(lspping_com_header->ts_sent_usec);
    ND_PRINT((ndo, "\n\t  Sender Timestamp: "));
    ts_print(ndo, &timestamp);

    timestamp.tv_sec=EXTRACT_32BITS(lspping_com_header->ts_rcvd_sec);
    timestamp.tv_usec=EXTRACT_32BITS(lspping_com_header->ts_rcvd_usec);
    ND_PRINT((ndo, "Receiver Timestamp: "));
    if ((timestamp.tv_sec != 0) && (timestamp.tv_usec != 0))
        ts_print(ndo, &timestamp);
    else
        ND_PRINT((ndo, "no timestamp"));

    tptr+=sizeof(const struct lspping_common_header);
    tlen-=sizeof(const struct lspping_common_header);

    while (tlen != 0) {
        /* Does the TLV go past the end of the packet? */
        if (tlen < sizeof(struct lspping_tlv_header))
            goto tooshort;

        /* did we capture enough for fully decoding the tlv header ? */
        ND_TCHECK2(*tptr, sizeof(struct lspping_tlv_header));

        lspping_tlv_header = (const struct lspping_tlv_header *)tptr;
        lspping_tlv_type=EXTRACT_16BITS(lspping_tlv_header->type);
        lspping_tlv_len=EXTRACT_16BITS(lspping_tlv_header->length);

        ND_PRINT((ndo, "\n\t  %s TLV (%u), length: %u",
               tok2str(lspping_tlv_values,
                       "Unknown",
                       lspping_tlv_type),
               lspping_tlv_type,
               lspping_tlv_len));

        /* some little sanity checking */
        if (lspping_tlv_len == 0) {
            tptr+=sizeof(struct lspping_tlv_header);
            tlen-=sizeof(struct lspping_tlv_header);
            continue;    /* no value to dissect */
        }

        tlv_tptr=tptr+sizeof(struct lspping_tlv_header);
        tlv_tlen=lspping_tlv_len; /* header not included -> no adjustment */

        /* Does the TLV go past the end of the packet? */
        if (tlen < lspping_tlv_len+sizeof(struct lspping_tlv_header))
            goto tooshort;
        /* did we capture enough for fully decoding the tlv ? */
        ND_TCHECK2(*tlv_tptr, lspping_tlv_len);
        tlv_hexdump=FALSE;

        switch(lspping_tlv_type) {
        case LSPPING_TLV_TARGET_FEC_STACK:
            while (tlv_tlen != 0) {
                /* Does the subTLV header go past the end of the TLV? */
                if (tlv_tlen < sizeof(struct lspping_tlv_header)) {
                    ND_PRINT((ndo, "\n\t      TLV is too short"));
                    tlv_hexdump = TRUE;
                    goto tlv_tooshort;
                }
                /* did we capture enough for fully decoding the subtlv header ? */
                ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_header));
                subtlv_hexdump=FALSE;

                lspping_subtlv_header = (const struct lspping_tlv_header *)tlv_tptr;
                lspping_subtlv_type=EXTRACT_16BITS(lspping_subtlv_header->type);
                lspping_subtlv_len=EXTRACT_16BITS(lspping_subtlv_header->length);
                subtlv_tptr=tlv_tptr+sizeof(struct lspping_tlv_header);

                /* Does the subTLV go past the end of the TLV? */
                if (tlv_tlen < lspping_subtlv_len+sizeof(struct lspping_tlv_header)) {
                    ND_PRINT((ndo, "\n\t      TLV is too short"));
                    tlv_hexdump = TRUE;
                    goto tlv_tooshort;
                }

                /* Did we capture enough for fully decoding the subTLV? */
                ND_TCHECK2(*subtlv_tptr, lspping_subtlv_len);

                ND_PRINT((ndo, "\n\t    %s subTLV (%u), length: %u",
                       tok2str(lspping_tlvtargetfec_subtlv_values,
                               "Unknown",
                               lspping_subtlv_type),
                       lspping_subtlv_type,
                       lspping_subtlv_len));

                switch(lspping_subtlv_type) {

                case LSPPING_TLV_TARGETFEC_SUBTLV_LDP_IPV4:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 5) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 5"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_ldp_ipv4 = \
                            (const struct lspping_tlv_targetfec_subtlv_ldp_ipv4_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      %s/%u",
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_ldp_ipv4->prefix),
                               subtlv_ptr.lspping_tlv_targetfec_subtlv_ldp_ipv4->prefix_len));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_LDP_IPV6:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 17) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 17"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_ldp_ipv6 = \
                            (const struct lspping_tlv_targetfec_subtlv_ldp_ipv6_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      %s/%u",
                               ip6addr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_ldp_ipv6->prefix),
                               subtlv_ptr.lspping_tlv_targetfec_subtlv_ldp_ipv6->prefix_len));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_BGP_IPV4:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 5) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 5"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_bgp_ipv4 = \
                            (const struct lspping_tlv_targetfec_subtlv_bgp_ipv4_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      %s/%u",
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_bgp_ipv4->prefix),
                               subtlv_ptr.lspping_tlv_targetfec_subtlv_bgp_ipv4->prefix_len));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_BGP_IPV6:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 17) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 17"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_bgp_ipv6 = \
                            (const struct lspping_tlv_targetfec_subtlv_bgp_ipv6_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      %s/%u",
                               ip6addr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_bgp_ipv6->prefix),
                               subtlv_ptr.lspping_tlv_targetfec_subtlv_bgp_ipv6->prefix_len));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_RSVP_IPV4:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 20) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 20"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv4 = \
                            (const struct lspping_tlv_targetfec_subtlv_rsvp_ipv4_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      tunnel end-point %s, tunnel sender %s, lsp-id 0x%04x" \
                               "\n\t      tunnel-id 0x%04x, extended tunnel-id %s",
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv4->tunnel_endpoint),
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv4->tunnel_sender),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv4->lsp_id),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv4->tunnel_id),
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv4->extended_tunnel_id)));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_RSVP_IPV6:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 56) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 56"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv6 = \
                            (const struct lspping_tlv_targetfec_subtlv_rsvp_ipv6_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      tunnel end-point %s, tunnel sender %s, lsp-id 0x%04x" \
                               "\n\t      tunnel-id 0x%04x, extended tunnel-id %s",
                               ip6addr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv6->tunnel_endpoint),
                               ip6addr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv6->tunnel_sender),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv6->lsp_id),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv6->tunnel_id),
                               ip6addr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_rsvp_ipv6->extended_tunnel_id)));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_L3VPN_IPV4:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 13) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 13"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv4 = \
                            (const struct lspping_tlv_targetfec_subtlv_l3vpn_ipv4_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      RD: %s, %s/%u",
                               bgp_vpn_rd_print(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv4->rd),
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv4->prefix),
                               subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv4->prefix_len));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_L3VPN_IPV6:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 25) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 25"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv6 = \
                            (const struct lspping_tlv_targetfec_subtlv_l3vpn_ipv6_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      RD: %s, %s/%u",
                               bgp_vpn_rd_print(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv6->rd),
                               ip6addr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv6->prefix),
                               subtlv_ptr.lspping_tlv_targetfec_subtlv_l3vpn_ipv6->prefix_len));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_L2VPN_ENDPT:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 14) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 14"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_endpt = \
                            (const struct lspping_tlv_targetfec_subtlv_l2vpn_endpt_t *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      RD: %s, Sender VE ID: %u, Receiver VE ID: %u" \
                               "\n\t      Encapsulation Type: %s (%u)",
                               bgp_vpn_rd_print(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_endpt->rd),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_endpt->sender_ve_id),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_endpt->receiver_ve_id),
                               tok2str(mpls_pw_types_values,
                                       "unknown",
                                       EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_endpt->encapsulation)),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_endpt->encapsulation)));
                    }
                    break;

                    /* the old L2VPN VCID subTLV does not have support for the sender field */
                case LSPPING_TLV_TARGETFEC_SUBTLV_FEC_128_PW_OLD:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 10) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 10"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid_old = \
                            (const struct lspping_tlv_targetfec_subtlv_fec_128_pw_old *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      Remote PE: %s" \
                               "\n\t      PW ID: 0x%08x, PW Type: %s (%u)",
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid_old->remote_pe_address),
                               EXTRACT_32BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid_old->pw_id),
                               tok2str(mpls_pw_types_values,
                                       "unknown",
                                       EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid_old->pw_type)),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid_old->pw_type)));
                    }
                    break;

                case LSPPING_TLV_TARGETFEC_SUBTLV_FEC_128_PW:
                    /* Is the subTLV length correct? */
                    if (lspping_subtlv_len != 14) {
                        ND_PRINT((ndo, "\n\t      invalid subTLV length, should be 14"));
                        subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    } else {
                        subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid = \
                            (const struct lspping_tlv_targetfec_subtlv_fec_128_pw *)subtlv_tptr;
                        ND_PRINT((ndo, "\n\t      Sender PE: %s, Remote PE: %s" \
                               "\n\t      PW ID: 0x%08x, PW Type: %s (%u)",
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid->sender_pe_address),
                               ipaddr_string(ndo, subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid->remote_pe_address),
                               EXTRACT_32BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid->pw_id),
                               tok2str(mpls_pw_types_values,
                                       "unknown",
                                       EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid->pw_type)),
                               EXTRACT_16BITS(subtlv_ptr.lspping_tlv_targetfec_subtlv_l2vpn_vcid->pw_type)));
                    }
                    break;

                default:
                    subtlv_hexdump=TRUE; /* unknown subTLV just hexdump it */
                    break;
                }
                /* do we want to see an additionally subtlv hexdump ? */
                if (ndo->ndo_vflag > 1 || subtlv_hexdump==TRUE)
                    print_unknown_data(ndo, tlv_tptr+sizeof(struct lspping_tlv_header), \
                                       "\n\t      ",
                                       lspping_subtlv_len);

                /* All subTLVs are aligned to four octet boundary */
                if (lspping_subtlv_len % 4) {
                    lspping_subtlv_len += 4 - (lspping_subtlv_len % 4);
                    /* Does the subTLV, including padding, go past the end of the TLV? */
                    if (tlv_tlen < lspping_subtlv_len+sizeof(struct lspping_tlv_header)) {
                        ND_PRINT((ndo, "\n\t\t TLV is too short"));
                        return;
                    }
                }
                tlv_tptr+=lspping_subtlv_len;
                tlv_tlen-=lspping_subtlv_len+sizeof(struct lspping_tlv_header);
            }
            break;

        case LSPPING_TLV_DOWNSTREAM_MAPPING:
            /* Does the header go past the end of the TLV? */
            if (tlv_tlen < sizeof(struct lspping_tlv_downstream_map_t)) {
                ND_PRINT((ndo, "\n\t      TLV is too short"));
                tlv_hexdump = TRUE;
                goto tlv_tooshort;
            }
            /* Did we capture enough to get the address family? */
            ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_downstream_map_t));

            tlv_ptr.lspping_tlv_downstream_map= \
                (const struct lspping_tlv_downstream_map_t *)tlv_tptr;

            /* that strange thing with the downstream map TLV is that until now
             * we do not know if its IPv4 or IPv6 or is unnumbered; after
             * we find the address-type, we recast the tlv_tptr and move on. */

            ND_PRINT((ndo, "\n\t    MTU: %u, Address-Type: %s (%u)",
                   EXTRACT_16BITS(tlv_ptr.lspping_tlv_downstream_map->mtu),
                   tok2str(lspping_tlv_downstream_addr_values,
                           "unknown",
                           tlv_ptr.lspping_tlv_downstream_map->address_type),
                   tlv_ptr.lspping_tlv_downstream_map->address_type));

            switch(tlv_ptr.lspping_tlv_downstream_map->address_type) {

            case LSPPING_AFI_IPV4:
                /* Does the data go past the end of the TLV? */
                if (tlv_tlen < sizeof(struct lspping_tlv_downstream_map_ipv4_t)) {
                    ND_PRINT((ndo, "\n\t      TLV is too short"));
                    tlv_hexdump = TRUE;
                    goto tlv_tooshort;
                }
                /* Did we capture enough for this part of the TLV? */
                ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_downstream_map_ipv4_t));

                tlv_ptr.lspping_tlv_downstream_map_ipv4= \
                    (const struct lspping_tlv_downstream_map_ipv4_t *)tlv_tptr;
                ND_PRINT((ndo, "\n\t    Downstream IP: %s" \
                       "\n\t    Downstream Interface IP: %s",
                       ipaddr_string(ndo, tlv_ptr.lspping_tlv_downstream_map_ipv4->downstream_ip),
                       ipaddr_string(ndo, tlv_ptr.lspping_tlv_downstream_map_ipv4->downstream_interface)));
                tlv_tptr+=sizeof(struct lspping_tlv_downstream_map_ipv4_t);
                tlv_tlen-=sizeof(struct lspping_tlv_downstream_map_ipv4_t);
                break;
            case LSPPING_AFI_IPV4_UNMB:
                /* Does the data go past the end of the TLV? */
                if (tlv_tlen < sizeof(struct lspping_tlv_downstream_map_ipv4_unmb_t)) {
                    ND_PRINT((ndo, "\n\t      TLV is too short"));
                    tlv_hexdump = TRUE;
                    goto tlv_tooshort;
                }
                /* Did we capture enough for this part of the TLV? */
                ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_downstream_map_ipv4_unmb_t));

                tlv_ptr.lspping_tlv_downstream_map_ipv4_unmb= \
                    (const struct lspping_tlv_downstream_map_ipv4_unmb_t *)tlv_tptr;
                ND_PRINT((ndo, "\n\t    Downstream IP: %s" \
                       "\n\t    Downstream Interface Index: 0x%08x",
                       ipaddr_string(ndo, tlv_ptr.lspping_tlv_downstream_map_ipv4_unmb->downstream_ip),
                       EXTRACT_32BITS(tlv_ptr.lspping_tlv_downstream_map_ipv4_unmb->downstream_interface)));
                tlv_tptr+=sizeof(struct lspping_tlv_downstream_map_ipv4_unmb_t);
                tlv_tlen-=sizeof(struct lspping_tlv_downstream_map_ipv4_unmb_t);
                break;
            case LSPPING_AFI_IPV6:
                /* Does the data go past the end of the TLV? */
                if (tlv_tlen < sizeof(struct lspping_tlv_downstream_map_ipv6_t)) {
                    ND_PRINT((ndo, "\n\t      TLV is too short"));
                    tlv_hexdump = TRUE;
                    goto tlv_tooshort;
                }
                /* Did we capture enough for this part of the TLV? */
                ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_downstream_map_ipv6_t));

                tlv_ptr.lspping_tlv_downstream_map_ipv6= \
                    (const struct lspping_tlv_downstream_map_ipv6_t *)tlv_tptr;
                ND_PRINT((ndo, "\n\t    Downstream IP: %s" \
                       "\n\t    Downstream Interface IP: %s",
                       ip6addr_string(ndo, tlv_ptr.lspping_tlv_downstream_map_ipv6->downstream_ip),
                       ip6addr_string(ndo, tlv_ptr.lspping_tlv_downstream_map_ipv6->downstream_interface)));
                tlv_tptr+=sizeof(struct lspping_tlv_downstream_map_ipv6_t);
                tlv_tlen-=sizeof(struct lspping_tlv_downstream_map_ipv6_t);
                break;
             case LSPPING_AFI_IPV6_UNMB:
                /* Does the data go past the end of the TLV? */
                if (tlv_tlen < sizeof(struct lspping_tlv_downstream_map_ipv6_unmb_t)) {
                    ND_PRINT((ndo, "\n\t      TLV is too short"));
                    tlv_hexdump = TRUE;
                    goto tlv_tooshort;
                }
                /* Did we capture enough for this part of the TLV? */
                ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_downstream_map_ipv6_unmb_t));

                tlv_ptr.lspping_tlv_downstream_map_ipv6_unmb= \
                   (const struct lspping_tlv_downstream_map_ipv6_unmb_t *)tlv_tptr;
                ND_PRINT((ndo, "\n\t    Downstream IP: %s" \
                       "\n\t    Downstream Interface Index: 0x%08x",
                       ip6addr_string(ndo, tlv_ptr.lspping_tlv_downstream_map_ipv6_unmb->downstream_ip),
                       EXTRACT_32BITS(tlv_ptr.lspping_tlv_downstream_map_ipv6_unmb->downstream_interface)));
                tlv_tptr+=sizeof(struct lspping_tlv_downstream_map_ipv6_unmb_t);
                tlv_tlen-=sizeof(struct lspping_tlv_downstream_map_ipv6_unmb_t);
                break;

            default:
                /* should not happen ! - no error message - tok2str() has barked already */
                break;
            }

            /* Does the data go past the end of the TLV? */
            if (tlv_tlen < sizeof(struct lspping_tlv_downstream_map_info_t)) {
                ND_PRINT((ndo, "\n\t      TLV is too short"));
                tlv_hexdump = TRUE;
                goto tlv_tooshort;
            }
            /* Did we capture enough for this part of the TLV? */
            ND_TCHECK2(*tlv_tptr, sizeof(struct lspping_tlv_downstream_map_info_t));

            tlv_ptr.lspping_tlv_downstream_map_info= \
                (const struct lspping_tlv_downstream_map_info_t *)tlv_tptr;

            /* FIXME add hash-key type, depth limit, multipath processing */

            tlv_tptr+=sizeof(struct lspping_tlv_downstream_map_info_t);
            tlv_tlen-=sizeof(struct lspping_tlv_downstream_map_info_t);

            /* FIXME print downstream labels */

            tlv_hexdump=TRUE; /* dump the TLV until code complete */

            break;

        case LSPPING_TLV_BFD_DISCRIMINATOR:
            if (tlv_tlen < LSPPING_TLV_BFD_DISCRIMINATOR_LEN) {
                ND_PRINT((ndo, "\n\t      TLV is too short"));
                tlv_hexdump = TRUE;
                goto tlv_tooshort;
            } else {
                ND_TCHECK2(*tptr, LSPPING_TLV_BFD_DISCRIMINATOR_LEN);
                ND_PRINT((ndo, "\n\t    BFD Discriminator 0x%08x", EXTRACT_32BITS(tptr)));
            }
            break;

        case  LSPPING_TLV_VENDOR_ENTERPRISE:
        {
            uint32_t vendor_id;

            if (tlv_tlen < LSPPING_TLV_VENDOR_ENTERPRISE_LEN) {
                ND_PRINT((ndo, "\n\t      TLV is too short"));
                tlv_hexdump = TRUE;
                goto tlv_tooshort;
            } else {
                ND_TCHECK2(*tptr, LSPPING_TLV_VENDOR_ENTERPRISE_LEN);
                vendor_id = EXTRACT_32BITS(tlv_tptr);
                ND_PRINT((ndo, "\n\t    Vendor: %s (0x%04x)",
                       tok2str(smi_values, "Unknown", vendor_id),
                       vendor_id));
            }
        }
            break;

            /*
             *  FIXME those are the defined TLVs that lack a decoder
             *  you are welcome to contribute code ;-)
             */
        case LSPPING_TLV_PAD:
        case LSPPING_TLV_ERROR_CODE:
        case LSPPING_TLV_VENDOR_PRIVATE:

        default:
            if (ndo->ndo_vflag <= 1)
                print_unknown_data(ndo, tlv_tptr, "\n\t    ", tlv_tlen);
            break;
        }
        /* do we want to see an additionally tlv hexdump ? */
    tlv_tooshort:
        if (ndo->ndo_vflag > 1 || tlv_hexdump==TRUE)
            print_unknown_data(ndo, tptr+sizeof(struct lspping_tlv_header), "\n\t    ",
                               lspping_tlv_len);


        /* All TLVs are aligned to four octet boundary */
        if (lspping_tlv_len % 4) {
            lspping_tlv_len += (4 - lspping_tlv_len % 4);
            /* Does the TLV, including padding, go past the end of the packet? */
            if (tlen < lspping_tlv_len+sizeof(struct lspping_tlv_header))
                goto tooshort;
        }

        tptr+=lspping_tlv_len+sizeof(struct lspping_tlv_header);
        tlen-=lspping_tlv_len+sizeof(struct lspping_tlv_header);
    }
    return;
tooshort:
    ND_PRINT((ndo, "\n\t\t packet is too short"));
    return;
trunc:
    ND_PRINT((ndo, "\n\t\t packet exceeded snapshot"));
    return;
}