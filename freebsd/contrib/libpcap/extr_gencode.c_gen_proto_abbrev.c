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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_AARP ; 
 int /*<<< orphan*/  ETHERTYPE_ARP ; 
 int /*<<< orphan*/  ETHERTYPE_ATALK ; 
 int /*<<< orphan*/  ETHERTYPE_DN ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int /*<<< orphan*/  ETHERTYPE_IPV6 ; 
 int /*<<< orphan*/  ETHERTYPE_LAT ; 
 int /*<<< orphan*/  ETHERTYPE_MOPDL ; 
 int /*<<< orphan*/  ETHERTYPE_MOPRC ; 
 int /*<<< orphan*/  ETHERTYPE_REVARP ; 
 int /*<<< orphan*/  ETHERTYPE_SCA ; 
 int /*<<< orphan*/  IPPROTO_AH ; 
 int /*<<< orphan*/  IPPROTO_CARP ; 
 int /*<<< orphan*/  IPPROTO_ESP ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  IPPROTO_IGMP ; 
 int /*<<< orphan*/  IPPROTO_IGRP ; 
 int /*<<< orphan*/  IPPROTO_PIM ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IPPROTO_VRRP ; 
 int /*<<< orphan*/  ISIS_L1_CSNP ; 
 int /*<<< orphan*/  ISIS_L1_LAN_IIH ; 
 int /*<<< orphan*/  ISIS_L1_LSP ; 
 int /*<<< orphan*/  ISIS_L1_PSNP ; 
 int /*<<< orphan*/  ISIS_L2_CSNP ; 
 int /*<<< orphan*/  ISIS_L2_LAN_IIH ; 
 int /*<<< orphan*/  ISIS_L2_LSP ; 
 int /*<<< orphan*/  ISIS_L2_PSNP ; 
 int /*<<< orphan*/  ISIS_PTP_IIH ; 
 int /*<<< orphan*/  ISO10589_ISIS ; 
 int /*<<< orphan*/  ISO8473_CLNP ; 
 int /*<<< orphan*/  ISO9542_ESIS ; 
 int /*<<< orphan*/  LLCSAP_8021D ; 
 int /*<<< orphan*/  LLCSAP_IPX ; 
 int /*<<< orphan*/  LLCSAP_ISONS ; 
 int /*<<< orphan*/  LLCSAP_NETBEUI ; 
#define  Q_AARP 166 
#define  Q_AH 165 
#define  Q_ARP 164 
#define  Q_ATALK 163 
#define  Q_CARP 162 
#define  Q_CLNP 161 
#define  Q_DECNET 160 
 int /*<<< orphan*/  Q_DEFAULT ; 
#define  Q_ESIS 159 
#define  Q_ESP 158 
#define  Q_ICMP 157 
#define  Q_ICMPV6 156 
#define  Q_IGMP 155 
#define  Q_IGRP 154 
#define  Q_IP 153 
#define  Q_IPV6 152 
#define  Q_IPX 151 
#define  Q_ISIS 150 
#define  Q_ISIS_CSNP 149 
#define  Q_ISIS_IIH 148 
#define  Q_ISIS_L1 147 
#define  Q_ISIS_L2 146 
#define  Q_ISIS_LSP 145 
#define  Q_ISIS_PSNP 144 
#define  Q_ISIS_SNP 143 
#define  Q_ISO 142 
#define  Q_LAT 141 
#define  Q_LINK 140 
#define  Q_MOPDL 139 
#define  Q_MOPRC 138 
#define  Q_NETBEUI 137 
#define  Q_PIM 136 
#define  Q_RADIO 135 
#define  Q_RARP 134 
#define  Q_SCA 133 
#define  Q_SCTP 132 
#define  Q_STP 131 
#define  Q_TCP 130 
#define  Q_UDP 129 
#define  Q_VRRP 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (int /*<<< orphan*/ *,char*) ; 
 struct block* gen_linktype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_proto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

struct block *
gen_proto_abbrev(compiler_state_t *cstate, int proto)
{
	struct block *b0;
	struct block *b1;

	switch (proto) {

	case Q_SCTP:
		b1 = gen_proto(cstate, IPPROTO_SCTP, Q_IP, Q_DEFAULT);
		b0 = gen_proto(cstate, IPPROTO_SCTP, Q_IPV6, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_TCP:
		b1 = gen_proto(cstate, IPPROTO_TCP, Q_IP, Q_DEFAULT);
		b0 = gen_proto(cstate, IPPROTO_TCP, Q_IPV6, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_UDP:
		b1 = gen_proto(cstate, IPPROTO_UDP, Q_IP, Q_DEFAULT);
		b0 = gen_proto(cstate, IPPROTO_UDP, Q_IPV6, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ICMP:
		b1 = gen_proto(cstate, IPPROTO_ICMP, Q_IP, Q_DEFAULT);
		break;

#ifndef	IPPROTO_IGMP
#define	IPPROTO_IGMP	2
#endif

	case Q_IGMP:
		b1 = gen_proto(cstate, IPPROTO_IGMP, Q_IP, Q_DEFAULT);
		break;

#ifndef	IPPROTO_IGRP
#define	IPPROTO_IGRP	9
#endif
	case Q_IGRP:
		b1 = gen_proto(cstate, IPPROTO_IGRP, Q_IP, Q_DEFAULT);
		break;

#ifndef IPPROTO_PIM
#define IPPROTO_PIM	103
#endif

	case Q_PIM:
		b1 = gen_proto(cstate, IPPROTO_PIM, Q_IP, Q_DEFAULT);
		b0 = gen_proto(cstate, IPPROTO_PIM, Q_IPV6, Q_DEFAULT);
		gen_or(b0, b1);
		break;

#ifndef IPPROTO_VRRP
#define IPPROTO_VRRP	112
#endif

	case Q_VRRP:
		b1 = gen_proto(cstate, IPPROTO_VRRP, Q_IP, Q_DEFAULT);
		break;

#ifndef IPPROTO_CARP
#define IPPROTO_CARP	112
#endif

	case Q_CARP:
		b1 = gen_proto(cstate, IPPROTO_CARP, Q_IP, Q_DEFAULT);
		break;

	case Q_IP:
		b1 = gen_linktype(cstate, ETHERTYPE_IP);
		break;

	case Q_ARP:
		b1 = gen_linktype(cstate, ETHERTYPE_ARP);
		break;

	case Q_RARP:
		b1 = gen_linktype(cstate, ETHERTYPE_REVARP);
		break;

	case Q_LINK:
		bpf_error(cstate, "link layer applied in wrong context");

	case Q_ATALK:
		b1 = gen_linktype(cstate, ETHERTYPE_ATALK);
		break;

	case Q_AARP:
		b1 = gen_linktype(cstate, ETHERTYPE_AARP);
		break;

	case Q_DECNET:
		b1 = gen_linktype(cstate, ETHERTYPE_DN);
		break;

	case Q_SCA:
		b1 = gen_linktype(cstate, ETHERTYPE_SCA);
		break;

	case Q_LAT:
		b1 = gen_linktype(cstate, ETHERTYPE_LAT);
		break;

	case Q_MOPDL:
		b1 = gen_linktype(cstate, ETHERTYPE_MOPDL);
		break;

	case Q_MOPRC:
		b1 = gen_linktype(cstate, ETHERTYPE_MOPRC);
		break;

	case Q_IPV6:
		b1 = gen_linktype(cstate, ETHERTYPE_IPV6);
		break;

#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6	58
#endif
	case Q_ICMPV6:
		b1 = gen_proto(cstate, IPPROTO_ICMPV6, Q_IPV6, Q_DEFAULT);
		break;

#ifndef IPPROTO_AH
#define IPPROTO_AH	51
#endif
	case Q_AH:
		b1 = gen_proto(cstate, IPPROTO_AH, Q_IP, Q_DEFAULT);
		b0 = gen_proto(cstate, IPPROTO_AH, Q_IPV6, Q_DEFAULT);
		gen_or(b0, b1);
		break;

#ifndef IPPROTO_ESP
#define IPPROTO_ESP	50
#endif
	case Q_ESP:
		b1 = gen_proto(cstate, IPPROTO_ESP, Q_IP, Q_DEFAULT);
		b0 = gen_proto(cstate, IPPROTO_ESP, Q_IPV6, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISO:
		b1 = gen_linktype(cstate, LLCSAP_ISONS);
		break;

	case Q_ESIS:
		b1 = gen_proto(cstate, ISO9542_ESIS, Q_ISO, Q_DEFAULT);
		break;

	case Q_ISIS:
		b1 = gen_proto(cstate, ISO10589_ISIS, Q_ISO, Q_DEFAULT);
		break;

	case Q_ISIS_L1: /* all IS-IS Level1 PDU-Types */
		b0 = gen_proto(cstate, ISIS_L1_LAN_IIH, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_PTP_IIH, Q_ISIS, Q_DEFAULT); /* FIXME extract the circuit-type bits */
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L1_LSP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L1_CSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L1_PSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISIS_L2: /* all IS-IS Level2 PDU-Types */
		b0 = gen_proto(cstate, ISIS_L2_LAN_IIH, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_PTP_IIH, Q_ISIS, Q_DEFAULT); /* FIXME extract the circuit-type bits */
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L2_LSP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L2_CSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L2_PSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISIS_IIH: /* all IS-IS Hello PDU-Types */
		b0 = gen_proto(cstate, ISIS_L1_LAN_IIH, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_L2_LAN_IIH, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_PTP_IIH, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISIS_LSP:
		b0 = gen_proto(cstate, ISIS_L1_LSP, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_L2_LSP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISIS_SNP:
		b0 = gen_proto(cstate, ISIS_L1_CSNP, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_L2_CSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L1_PSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		b0 = gen_proto(cstate, ISIS_L2_PSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISIS_CSNP:
		b0 = gen_proto(cstate, ISIS_L1_CSNP, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_L2_CSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_ISIS_PSNP:
		b0 = gen_proto(cstate, ISIS_L1_PSNP, Q_ISIS, Q_DEFAULT);
		b1 = gen_proto(cstate, ISIS_L2_PSNP, Q_ISIS, Q_DEFAULT);
		gen_or(b0, b1);
		break;

	case Q_CLNP:
		b1 = gen_proto(cstate, ISO8473_CLNP, Q_ISO, Q_DEFAULT);
		break;

	case Q_STP:
		b1 = gen_linktype(cstate, LLCSAP_8021D);
		break;

	case Q_IPX:
		b1 = gen_linktype(cstate, LLCSAP_IPX);
		break;

	case Q_NETBEUI:
		b1 = gen_linktype(cstate, LLCSAP_NETBEUI);
		break;

	case Q_RADIO:
		bpf_error(cstate, "'radio' is not a valid protocol type");

	default:
		abort();
	}
	return b1;
}