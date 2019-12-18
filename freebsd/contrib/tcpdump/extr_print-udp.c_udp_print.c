#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_59__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  const u_char ;
struct udphdr {scalar_t__ uh_dport; scalar_t__ uh_sport; scalar_t__ uh_ulen; scalar_t__ uh_sum; } ;
struct sunrpc_msg {scalar_t__ rm_direction; scalar_t__ rm_xid; } ;
struct ip6_hdr {scalar_t__ ip6_plen; } ;
struct ip {int dummy; } ;
struct LAP {scalar_t__ type; } ;
struct TYPE_59__ {int ndo_packettype; int ndo_vflag; int /*<<< orphan*/  ndo_qflag; int /*<<< orphan*/  ndo_Kflag; int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  enum sunrpc_msg_type { ____Placeholder_sunrpc_msg_type } sunrpc_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  AHCP_PORT ; 
 int /*<<< orphan*/  AODV_PORT ; 
 int /*<<< orphan*/  BABEL_PORT ; 
 int /*<<< orphan*/  BABEL_PORT_OLD ; 
 int BFD_CONTROL_PORT ; 
 int BFD_ECHO_PORT ; 
 int /*<<< orphan*/  BOOTPC_PORT ; 
 int /*<<< orphan*/  BOOTPS_PORT ; 
 int /*<<< orphan*/  CISCO_AUTORP_PORT ; 
 int /*<<< orphan*/  DHCP6_CLI_PORT ; 
 int /*<<< orphan*/  DHCP6_SERV_PORT ; 
 int EXTRACT_16BITS (scalar_t__*) ; 
 scalar_t__ EXTRACT_32BITS (scalar_t__*) ; 
 int /*<<< orphan*/  GENEVE_PORT ; 
 int /*<<< orphan*/  HNCP_PORT ; 
 int HSRP_PORT ; 
 int IP_V (struct ip const*) ; 
 int /*<<< orphan*/  ISAKMP_PORT ; 
 int /*<<< orphan*/  ISAKMP_PORT_NATT ; 
 int /*<<< orphan*/  ISAKMP_PORT_USER1 ; 
 int /*<<< orphan*/  ISAKMP_PORT_USER2 ; 
 scalar_t__ IS_SRC_OR_DST_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERBEROS_PORT ; 
 int /*<<< orphan*/  KERBEROS_SEC_PORT ; 
 int /*<<< orphan*/  L2TP_PORT ; 
 int /*<<< orphan*/  LDP_PORT ; 
 int /*<<< orphan*/  LISP_CONTROL_PORT ; 
 int /*<<< orphan*/  LMP_PORT ; 
 int LWAPP_CONTROL_PORT ; 
 int /*<<< orphan*/  LWAPP_DATA_PORT ; 
 int /*<<< orphan*/  LWRES_PORT ; 
 int /*<<< orphan*/  MPLS_LSP_PING_PORT ; 
 int /*<<< orphan*/  MULTICASTDNS_PORT ; 
 int /*<<< orphan*/  NAMESERVER_PORT ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ ND_TTEST (scalar_t__) ; 
 scalar_t__ ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  NETBIOS_DGRAM_PORT ; 
 int /*<<< orphan*/  NETBIOS_NS_PORT ; 
 int NFS_PORT ; 
 int /*<<< orphan*/  NTP_PORT ; 
 int /*<<< orphan*/  OLSR_PORT ; 
 int /*<<< orphan*/  OTV_PORT ; 
#define  PT_AODV 141 
#define  PT_CNFP 140 
#define  PT_LMP 139 
#define  PT_PGM 138 
#define  PT_PGM_ZMTP1 137 
#define  PT_RADIUS 136 
#define  PT_RPC 135 
#define  PT_RTCP 134 
#define  PT_RTP 133 
#define  PT_SNMP 132 
#define  PT_TFTP 131 
#define  PT_VAT 130 
#define  PT_VXLAN 129 
#define  PT_WB 128 
 int /*<<< orphan*/  RADIUS_ACCOUNTING_PORT ; 
 int /*<<< orphan*/  RADIUS_CISCO_COA_PORT ; 
 int /*<<< orphan*/  RADIUS_COA_PORT ; 
 int /*<<< orphan*/  RADIUS_NEW_ACCOUNTING_PORT ; 
 int /*<<< orphan*/  RADIUS_NEW_PORT ; 
 int /*<<< orphan*/  RADIUS_PORT ; 
 int /*<<< orphan*/  RIPNG_PORT ; 
 int /*<<< orphan*/  RIP_PORT ; 
 int RX_PORT_HIGH ; 
 int RX_PORT_LOW ; 
 int /*<<< orphan*/  SFLOW_PORT ; 
 int /*<<< orphan*/  SIP_PORT ; 
 int /*<<< orphan*/  SNMPTRAP_PORT ; 
 int /*<<< orphan*/  SNMP_PORT ; 
 int SUNRPC_CALL ; 
 int SUNRPC_PORT ; 
 int SUNRPC_REPLY ; 
 int /*<<< orphan*/  SYSLOG_PORT ; 
 int /*<<< orphan*/  TFTP_PORT ; 
 int /*<<< orphan*/  TIMED_PORT ; 
 int VAT_PORT ; 
 int /*<<< orphan*/  VQP_PORT ; 
 int /*<<< orphan*/  VXLAN_GPE_PORT ; 
 int /*<<< orphan*/  VXLAN_PORT ; 
 int WB_PORT ; 
 int /*<<< orphan*/  ZEPHYR_CLT_PORT ; 
 int /*<<< orphan*/  ZEPHYR_SRV_PORT ; 
 int /*<<< orphan*/  ahcp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  aodv_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atalk_port (int) ; 
 int /*<<< orphan*/  babel_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bfd_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  bootp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cisco_autorp_print (TYPE_1__*,void const*,int) ; 
 int /*<<< orphan*/  cnfp_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dhcp6_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  geneve_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hncp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hsrp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  in_cksum_shouldbe (int,int) ; 
 int /*<<< orphan*/  isakmp_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  isakmp_rfc3948_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  krb_print (TYPE_1__*,void const*) ; 
 int /*<<< orphan*/  l2tp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ lapDDP ; 
 int /*<<< orphan*/  ldp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lisp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  llap_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lmp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lspping_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lwapp_control_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  lwapp_data_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lwres_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  nbt_udp137_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  nbt_udp138_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  nfsreply_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfsreply_print_noaddr (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfsreq_print_noaddr (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ns_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ntp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  olsr_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  otv_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pgm_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  radius_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  rip_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ripng_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* rtcp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rtp_print (TYPE_1__*,void const*,int,struct udphdr const*) ; 
 int /*<<< orphan*/  rx_print (TYPE_1__*,void const*,int,int,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sflow_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sip_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  snmp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sunrpcrequest_print (TYPE_1__*,int,int,...) ; 
 int /*<<< orphan*/  syslog_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tftp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  timed_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int udp6_cksum (TYPE_1__*,struct ip6_hdr const*,struct udphdr const*,int) ; 
 int udp_cksum (TYPE_1__*,struct ip const*,struct udphdr const*,int) ; 
 int /*<<< orphan*/  udp_tstr ; 
 int /*<<< orphan*/  udpipaddr_print (TYPE_1__*,struct ip const*,int,int) ; 
 int /*<<< orphan*/  vat_print (TYPE_1__*,void const*,struct udphdr const*) ; 
 int /*<<< orphan*/  vqp_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  vxlan_gpe_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  vxlan_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wb_print (TYPE_1__*,void const*,int) ; 
 int /*<<< orphan*/  zephyr_print (TYPE_1__*,void const*,int) ; 

void
udp_print(netdissect_options *ndo, register const u_char *bp, u_int length,
	  register const u_char *bp2, int fragmented)
{
	register const struct udphdr *up;
	register const struct ip *ip;
	register const u_char *cp;
	register const u_char *ep = bp + length;
	uint16_t sport, dport, ulen;
	register const struct ip6_hdr *ip6;

	if (ep > ndo->ndo_snapend)
		ep = ndo->ndo_snapend;
	up = (const struct udphdr *)bp;
	ip = (const struct ip *)bp2;
	if (IP_V(ip) == 6)
		ip6 = (const struct ip6_hdr *)bp2;
	else
		ip6 = NULL;
	if (!ND_TTEST(up->uh_dport)) {
		udpipaddr_print(ndo, ip, -1, -1);
		goto trunc;
	}

	sport = EXTRACT_16BITS(&up->uh_sport);
	dport = EXTRACT_16BITS(&up->uh_dport);

	if (length < sizeof(struct udphdr)) {
		udpipaddr_print(ndo, ip, sport, dport);
		ND_PRINT((ndo, "truncated-udp %d", length));
		return;
	}
	if (!ND_TTEST(up->uh_ulen)) {
		udpipaddr_print(ndo, ip, sport, dport);
		goto trunc;
	}
	ulen = EXTRACT_16BITS(&up->uh_ulen);
	if (ulen < sizeof(struct udphdr)) {
		udpipaddr_print(ndo, ip, sport, dport);
		ND_PRINT((ndo, "truncated-udplength %d", ulen));
		return;
	}
	ulen -= sizeof(struct udphdr);
	length -= sizeof(struct udphdr);
	if (ulen < length)
		length = ulen;

	cp = (const u_char *)(up + 1);
	if (cp > ndo->ndo_snapend) {
		udpipaddr_print(ndo, ip, sport, dport);
		goto trunc;
	}

	if (ndo->ndo_packettype) {
		register const struct sunrpc_msg *rp;
		enum sunrpc_msg_type direction;

		switch (ndo->ndo_packettype) {

		case PT_VAT:
			udpipaddr_print(ndo, ip, sport, dport);
			vat_print(ndo, (const void *)(up + 1), up);
			break;

		case PT_WB:
			udpipaddr_print(ndo, ip, sport, dport);
			wb_print(ndo, (const void *)(up + 1), length);
			break;

		case PT_RPC:
			rp = (const struct sunrpc_msg *)(up + 1);
			direction = (enum sunrpc_msg_type)EXTRACT_32BITS(&rp->rm_direction);
			if (direction == SUNRPC_CALL)
				sunrpcrequest_print(ndo, (const u_char *)rp, length,
				    (const u_char *)ip);
			else
				nfsreply_print(ndo, (const u_char *)rp, length,
				    (const u_char *)ip);			/*XXX*/
			break;

		case PT_RTP:
			udpipaddr_print(ndo, ip, sport, dport);
			rtp_print(ndo, (const void *)(up + 1), length, up);
			break;

		case PT_RTCP:
			udpipaddr_print(ndo, ip, sport, dport);
			while (cp < ep)
				cp = rtcp_print(ndo, cp, ep);
			break;

		case PT_SNMP:
			udpipaddr_print(ndo, ip, sport, dport);
			snmp_print(ndo, (const u_char *)(up + 1), length);
			break;

		case PT_CNFP:
			udpipaddr_print(ndo, ip, sport, dport);
			cnfp_print(ndo, cp);
			break;

		case PT_TFTP:
			udpipaddr_print(ndo, ip, sport, dport);
			tftp_print(ndo, cp, length);
			break;

		case PT_AODV:
			udpipaddr_print(ndo, ip, sport, dport);
			aodv_print(ndo, (const u_char *)(up + 1), length,
			    ip6 != NULL);
			break;

		case PT_RADIUS:
			udpipaddr_print(ndo, ip, sport, dport);
			radius_print(ndo, cp, length);
			break;

		case PT_VXLAN:
			udpipaddr_print(ndo, ip, sport, dport);
			vxlan_print(ndo, (const u_char *)(up + 1), length);
			break;

		case PT_PGM:
		case PT_PGM_ZMTP1:
			udpipaddr_print(ndo, ip, sport, dport);
			pgm_print(ndo, cp, length, bp2);
			break;
		case PT_LMP:
			udpipaddr_print(ndo, ip, sport, dport);
			lmp_print(ndo, cp, length);
			break;
		}
		return;
	}

	udpipaddr_print(ndo, ip, sport, dport);
	if (!ndo->ndo_qflag) {
		register const struct sunrpc_msg *rp;
		enum sunrpc_msg_type direction;

		rp = (const struct sunrpc_msg *)(up + 1);
		if (ND_TTEST(rp->rm_direction)) {
			direction = (enum sunrpc_msg_type)EXTRACT_32BITS(&rp->rm_direction);
			if (dport == NFS_PORT && direction == SUNRPC_CALL) {
				ND_PRINT((ndo, "NFS request xid %u ", EXTRACT_32BITS(&rp->rm_xid)));
				nfsreq_print_noaddr(ndo, (const u_char *)rp, length,
				    (const u_char *)ip);
				return;
			}
			if (sport == NFS_PORT && direction == SUNRPC_REPLY) {
				ND_PRINT((ndo, "NFS reply xid %u ", EXTRACT_32BITS(&rp->rm_xid)));
				nfsreply_print_noaddr(ndo, (const u_char *)rp, length,
				    (const u_char *)ip);
				return;
			}
#ifdef notdef
			if (dport == SUNRPC_PORT && direction == SUNRPC_CALL) {
				sunrpcrequest_print((const u_char *)rp, length, (const u_char *)ip);
				return;
			}
#endif
		}
	}

	if (ndo->ndo_vflag && !ndo->ndo_Kflag && !fragmented) {
                /* Check the checksum, if possible. */
                uint16_t sum, udp_sum;

		/*
		 * XXX - do this even if vflag == 1?
		 * TCP does, and we do so for UDP-over-IPv6.
		 */
	        if (IP_V(ip) == 4 && (ndo->ndo_vflag > 1)) {
			udp_sum = EXTRACT_16BITS(&up->uh_sum);
			if (udp_sum == 0) {
				ND_PRINT((ndo, "[no cksum] "));
			} else if (ND_TTEST2(cp[0], length)) {
				sum = udp_cksum(ndo, ip, up, length + sizeof(struct udphdr));

	                        if (sum != 0) {
					ND_PRINT((ndo, "[bad udp cksum 0x%04x -> 0x%04x!] ",
					    udp_sum,
					    in_cksum_shouldbe(udp_sum, sum)));
				} else
					ND_PRINT((ndo, "[udp sum ok] "));
			}
		}
		else if (IP_V(ip) == 6 && ip6->ip6_plen) {
			/* for IPv6, UDP checksum is mandatory */
			if (ND_TTEST2(cp[0], length)) {
				sum = udp6_cksum(ndo, ip6, up, length + sizeof(struct udphdr));
				udp_sum = EXTRACT_16BITS(&up->uh_sum);

	                        if (sum != 0) {
					ND_PRINT((ndo, "[bad udp cksum 0x%04x -> 0x%04x!] ",
					    udp_sum,
					    in_cksum_shouldbe(udp_sum, sum)));
				} else
					ND_PRINT((ndo, "[udp sum ok] "));
			}
		}
	}

	if (!ndo->ndo_qflag) {
		if (IS_SRC_OR_DST_PORT(NAMESERVER_PORT))
			ns_print(ndo, (const u_char *)(up + 1), length, 0);
		else if (IS_SRC_OR_DST_PORT(MULTICASTDNS_PORT))
			ns_print(ndo, (const u_char *)(up + 1), length, 1);
		else if (IS_SRC_OR_DST_PORT(TIMED_PORT))
			timed_print(ndo, (const u_char *)(up + 1));
		else if (IS_SRC_OR_DST_PORT(TFTP_PORT))
			tftp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(BOOTPC_PORT) || IS_SRC_OR_DST_PORT(BOOTPS_PORT))
			bootp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(RIP_PORT))
			rip_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(AODV_PORT))
			aodv_print(ndo, (const u_char *)(up + 1), length,
			    ip6 != NULL);
	        else if (IS_SRC_OR_DST_PORT(ISAKMP_PORT))
			 isakmp_print(ndo, (const u_char *)(up + 1), length, bp2);
	        else if (IS_SRC_OR_DST_PORT(ISAKMP_PORT_NATT))
			 isakmp_rfc3948_print(ndo, (const u_char *)(up + 1), length, bp2);
#if 1 /*???*/
	        else if (IS_SRC_OR_DST_PORT(ISAKMP_PORT_USER1) || IS_SRC_OR_DST_PORT(ISAKMP_PORT_USER2))
			isakmp_print(ndo, (const u_char *)(up + 1), length, bp2);
#endif
		else if (IS_SRC_OR_DST_PORT(SNMP_PORT) || IS_SRC_OR_DST_PORT(SNMPTRAP_PORT))
			snmp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(NTP_PORT))
			ntp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(KERBEROS_PORT) || IS_SRC_OR_DST_PORT(KERBEROS_SEC_PORT))
			krb_print(ndo, (const void *)(up + 1));
		else if (IS_SRC_OR_DST_PORT(L2TP_PORT))
			l2tp_print(ndo, (const u_char *)(up + 1), length);
#ifdef ENABLE_SMB
		else if (IS_SRC_OR_DST_PORT(NETBIOS_NS_PORT))
			nbt_udp137_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(NETBIOS_DGRAM_PORT))
			nbt_udp138_print(ndo, (const u_char *)(up + 1), length);
#endif
		else if (dport == VAT_PORT)
			vat_print(ndo, (const void *)(up + 1), up);
		else if (IS_SRC_OR_DST_PORT(ZEPHYR_SRV_PORT) || IS_SRC_OR_DST_PORT(ZEPHYR_CLT_PORT))
			zephyr_print(ndo, (const void *)(up + 1), length);
		/*
		 * Since there are 10 possible ports to check, I think
		 * a <> test would be more efficient
		 */
		else if ((sport >= RX_PORT_LOW && sport <= RX_PORT_HIGH) ||
			 (dport >= RX_PORT_LOW && dport <= RX_PORT_HIGH))
			rx_print(ndo, (const void *)(up + 1), length, sport, dport,
				 (const u_char *) ip);
		else if (IS_SRC_OR_DST_PORT(RIPNG_PORT))
			ripng_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(DHCP6_SERV_PORT) || IS_SRC_OR_DST_PORT(DHCP6_CLI_PORT))
			dhcp6_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(AHCP_PORT))
			ahcp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(BABEL_PORT) || IS_SRC_OR_DST_PORT(BABEL_PORT_OLD))
			babel_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(HNCP_PORT))
			hncp_print(ndo, (const u_char *)(up + 1), length);
		/*
		 * Kludge in test for whiteboard packets.
		 */
		else if (dport == WB_PORT)
			wb_print(ndo, (const void *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(CISCO_AUTORP_PORT))
			cisco_autorp_print(ndo, (const void *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(RADIUS_PORT) ||
			 IS_SRC_OR_DST_PORT(RADIUS_NEW_PORT) ||
			 IS_SRC_OR_DST_PORT(RADIUS_ACCOUNTING_PORT) ||
			 IS_SRC_OR_DST_PORT(RADIUS_NEW_ACCOUNTING_PORT) ||
			 IS_SRC_OR_DST_PORT(RADIUS_CISCO_COA_PORT) ||
			 IS_SRC_OR_DST_PORT(RADIUS_COA_PORT) )
			radius_print(ndo, (const u_char *)(up+1), length);
		else if (dport == HSRP_PORT)
			hsrp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(LWRES_PORT))
			lwres_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(LDP_PORT))
			ldp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(OLSR_PORT))
			olsr_print(ndo, (const u_char *)(up + 1), length,
					(IP_V(ip) == 6) ? 1 : 0);
		else if (IS_SRC_OR_DST_PORT(MPLS_LSP_PING_PORT))
			lspping_print(ndo, (const u_char *)(up + 1), length);
		else if (dport == BFD_CONTROL_PORT ||
			 dport == BFD_ECHO_PORT )
			bfd_print(ndo, (const u_char *)(up+1), length, dport);
                else if (IS_SRC_OR_DST_PORT(LMP_PORT))
			lmp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(VQP_PORT))
			vqp_print(ndo, (const u_char *)(up + 1), length);
                else if (IS_SRC_OR_DST_PORT(SFLOW_PORT))
                        sflow_print(ndo, (const u_char *)(up + 1), length);
	        else if (dport == LWAPP_CONTROL_PORT)
			lwapp_control_print(ndo, (const u_char *)(up + 1), length, 1);
                else if (sport == LWAPP_CONTROL_PORT)
                        lwapp_control_print(ndo, (const u_char *)(up + 1), length, 0);
                else if (IS_SRC_OR_DST_PORT(LWAPP_DATA_PORT))
                        lwapp_data_print(ndo, (const u_char *)(up + 1), length);
                else if (IS_SRC_OR_DST_PORT(SIP_PORT))
			sip_print(ndo, (const u_char *)(up + 1), length);
                else if (IS_SRC_OR_DST_PORT(SYSLOG_PORT))
			syslog_print(ndo, (const u_char *)(up + 1), length);
                else if (IS_SRC_OR_DST_PORT(OTV_PORT))
			otv_print(ndo, (const u_char *)(up + 1), length);
                else if (IS_SRC_OR_DST_PORT(VXLAN_PORT))
			vxlan_print(ndo, (const u_char *)(up + 1), length);
                else if (IS_SRC_OR_DST_PORT(GENEVE_PORT))
			geneve_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(LISP_CONTROL_PORT))
			lisp_print(ndo, (const u_char *)(up + 1), length);
		else if (IS_SRC_OR_DST_PORT(VXLAN_GPE_PORT))
			vxlan_gpe_print(ndo, (const u_char *)(up + 1), length);
		else if (ND_TTEST(((const struct LAP *)cp)->type) &&
		    ((const struct LAP *)cp)->type == lapDDP &&
		    (atalk_port(sport) || atalk_port(dport))) {
			if (ndo->ndo_vflag)
				ND_PRINT((ndo, "kip "));
			llap_print(ndo, cp, length);
		} else {
			if (ulen > length)
				ND_PRINT((ndo, "UDP, bad length %u > %u",
				    ulen, length));
			else
				ND_PRINT((ndo, "UDP, length %u", ulen));
		}
	} else {
		if (ulen > length)
			ND_PRINT((ndo, "UDP, bad length %u > %u",
			    ulen, length));
		else
			ND_PRINT((ndo, "UDP, length %u", ulen));
	}
	return;

trunc:
	ND_PRINT((ndo, "%s", udp_tstr));
}