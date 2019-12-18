#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  label_stack_depth; } ;
typedef  TYPE_1__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_ARP ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int /*<<< orphan*/  ETHERTYPE_REVARP ; 
#define  Q_AARP 159 
#define  Q_AH 158 
#define  Q_ARP 157 
#define  Q_ATALK 156 
#define  Q_CARP 155 
#define  Q_CLNP 154 
#define  Q_DECNET 153 
#define  Q_DEFAULT 152 
#define  Q_ESIS 151 
#define  Q_ESP 150 
#define  Q_ICMP 149 
#define  Q_ICMPV6 148 
#define  Q_IGMP 147 
#define  Q_IGRP 146 
#define  Q_IP 145 
#define  Q_IPV6 144 
#define  Q_IPX 143 
#define  Q_ISIS 142 
#define  Q_ISO 141 
#define  Q_LAT 140 
#define  Q_MOPDL 139 
#define  Q_MOPRC 138 
 int Q_NET ; 
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
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*,...) ; 
 struct block* gen_dnhostop (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct block* gen_hostop (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 

__attribute__((used)) static struct block *
gen_host(compiler_state_t *cstate, bpf_u_int32 addr, bpf_u_int32 mask,
    int proto, int dir, int type)
{
	struct block *b0, *b1;
	const char *typestr;

	if (type == Q_NET)
		typestr = "net";
	else
		typestr = "host";

	switch (proto) {

	case Q_DEFAULT:
		b0 = gen_host(cstate, addr, mask, Q_IP, dir, type);
		/*
		 * Only check for non-IPv4 addresses if we're not
		 * checking MPLS-encapsulated packets.
		 */
		if (cstate->label_stack_depth == 0) {
			b1 = gen_host(cstate, addr, mask, Q_ARP, dir, type);
			gen_or(b0, b1);
			b0 = gen_host(cstate, addr, mask, Q_RARP, dir, type);
			gen_or(b1, b0);
		}
		return b0;

	case Q_IP:
		return gen_hostop(cstate, addr, mask, dir, ETHERTYPE_IP, 12, 16);

	case Q_RARP:
		return gen_hostop(cstate, addr, mask, dir, ETHERTYPE_REVARP, 14, 24);

	case Q_ARP:
		return gen_hostop(cstate, addr, mask, dir, ETHERTYPE_ARP, 14, 24);

	case Q_TCP:
		bpf_error(cstate, "'tcp' modifier applied to %s", typestr);

	case Q_SCTP:
		bpf_error(cstate, "'sctp' modifier applied to %s", typestr);

	case Q_UDP:
		bpf_error(cstate, "'udp' modifier applied to %s", typestr);

	case Q_ICMP:
		bpf_error(cstate, "'icmp' modifier applied to %s", typestr);

	case Q_IGMP:
		bpf_error(cstate, "'igmp' modifier applied to %s", typestr);

	case Q_IGRP:
		bpf_error(cstate, "'igrp' modifier applied to %s", typestr);

	case Q_PIM:
		bpf_error(cstate, "'pim' modifier applied to %s", typestr);

	case Q_VRRP:
		bpf_error(cstate, "'vrrp' modifier applied to %s", typestr);

	case Q_CARP:
		bpf_error(cstate, "'carp' modifier applied to %s", typestr);

	case Q_ATALK:
		bpf_error(cstate, "ATALK host filtering not implemented");

	case Q_AARP:
		bpf_error(cstate, "AARP host filtering not implemented");

	case Q_DECNET:
		return gen_dnhostop(cstate, addr, dir);

	case Q_SCA:
		bpf_error(cstate, "SCA host filtering not implemented");

	case Q_LAT:
		bpf_error(cstate, "LAT host filtering not implemented");

	case Q_MOPDL:
		bpf_error(cstate, "MOPDL host filtering not implemented");

	case Q_MOPRC:
		bpf_error(cstate, "MOPRC host filtering not implemented");

	case Q_IPV6:
		bpf_error(cstate, "'ip6' modifier applied to ip host");

	case Q_ICMPV6:
		bpf_error(cstate, "'icmp6' modifier applied to %s", typestr);

	case Q_AH:
		bpf_error(cstate, "'ah' modifier applied to %s", typestr);

	case Q_ESP:
		bpf_error(cstate, "'esp' modifier applied to %s", typestr);

	case Q_ISO:
		bpf_error(cstate, "ISO host filtering not implemented");

	case Q_ESIS:
		bpf_error(cstate, "'esis' modifier applied to %s", typestr);

	case Q_ISIS:
		bpf_error(cstate, "'isis' modifier applied to %s", typestr);

	case Q_CLNP:
		bpf_error(cstate, "'clnp' modifier applied to %s", typestr);

	case Q_STP:
		bpf_error(cstate, "'stp' modifier applied to %s", typestr);

	case Q_IPX:
		bpf_error(cstate, "IPX host filtering not implemented");

	case Q_NETBEUI:
		bpf_error(cstate, "'netbeui' modifier applied to %s", typestr);

	case Q_RADIO:
		bpf_error(cstate, "'radio' modifier applied to %s", typestr);

	default:
		abort();
	}
	/* NOTREACHED */
}