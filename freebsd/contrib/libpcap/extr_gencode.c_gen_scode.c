#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_24__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct qual {int proto; int dir; int addr; } ;
struct in6_addr {int dummy; } ;
struct block {int dummy; } ;
struct addrinfo {scalar_t__ ai_addr; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  mask128 ;
struct TYPE_23__ {int /*<<< orphan*/  constant_part; } ;
struct TYPE_25__ {struct addrinfo* ai; TYPE_1__ off_linktype; int /*<<< orphan*/  linktype; } ;
typedef  TYPE_3__ compiler_state_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
#define  AF_INET 149 
#define  AF_INET6 148 
#define  DLT_EN10MB 147 
#define  DLT_FDDI 146 
#define  DLT_IEEE802 145 
#define  DLT_IEEE802_11 144 
#define  DLT_IEEE802_11_RADIO 143 
#define  DLT_IEEE802_11_RADIO_AVS 142 
#define  DLT_IP_OVER_FC 141 
#define  DLT_NETANALYZER 140 
#define  DLT_NETANALYZER_TRANSPARENT 139 
#define  DLT_PPI 138 
#define  DLT_PRISM_HEADER 137 
 int IPPROTO_SCTP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  OFFSET_NOT_SET ; 
 int Q_DECNET ; 
#define  Q_DEFAULT 136 
#define  Q_GATEWAY 135 
#define  Q_HOST 134 
 int Q_IP ; 
 int Q_IPV6 ; 
 int Q_LINK ; 
#define  Q_NET 133 
#define  Q_PORT 132 
#define  Q_PORTRANGE 131 
#define  Q_PROTO 130 
#define  Q_PROTOCHAIN 129 
 int Q_SCTP ; 
 int Q_TCP ; 
 int Q_UDP ; 
#define  Q_UNDEF 128 
 int /*<<< orphan*/  __pcap_nametodnaddr (char const*,unsigned short*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_ehostop (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 struct block* gen_fhostop (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 struct block* gen_gateway (TYPE_3__*,int /*<<< orphan*/ *,struct addrinfo*,int,int) ; 
 struct block* gen_host (TYPE_3__*,unsigned short,int,int,int,int) ; 
 struct block* gen_host6 (TYPE_3__*,int /*<<< orphan*/ *,struct in6_addr*,int,int,int) ; 
 struct block* gen_ipfchostop (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_port (TYPE_3__*,int,int,int) ; 
 struct block* gen_port6 (TYPE_3__*,int,int,int) ; 
 struct block* gen_portrange (TYPE_3__*,int,int,int,int) ; 
 struct block* gen_portrange6 (TYPE_3__*,int,int,int,int) ; 
 struct block* gen_prevlinkhdr_check (TYPE_3__*) ; 
 struct block* gen_proto (TYPE_3__*,int,int,int) ; 
 struct block* gen_protochain (TYPE_3__*,int,int,int) ; 
 struct block* gen_thostop (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 struct block* gen_wlanhostop (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int lookup_proto (TYPE_3__*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int,int) ; 
 unsigned short ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcap_ether_hostton (char const*) ; 
 struct addrinfo* pcap_nametoaddrinfo (char const*) ; 
 int pcap_nametonetaddr (char const*) ; 
 int /*<<< orphan*/  pcap_nametoport (char const*,int*,int*) ; 
 int /*<<< orphan*/  pcap_nametoportrange (char const*,int*,int*,int*) ; 
 int /*<<< orphan*/  syntax (TYPE_3__*) ; 

struct block *
gen_scode(compiler_state_t *cstate, const char *name, struct qual q)
{
	int proto = q.proto;
	int dir = q.dir;
	int tproto;
	u_char *eaddr;
	bpf_u_int32 mask, addr;
	struct addrinfo *res, *res0;
	struct sockaddr_in *sin4;
#ifdef INET6
	int tproto6;
	struct sockaddr_in6 *sin6;
	struct in6_addr mask128;
#endif /*INET6*/
	struct block *b, *tmp;
	int port, real_proto;
	int port1, port2;

	switch (q.addr) {

	case Q_NET:
		addr = pcap_nametonetaddr(name);
		if (addr == 0)
			bpf_error(cstate, "unknown network '%s'", name);
		/* Left justify network addr and calculate its network mask */
		mask = 0xffffffff;
		while (addr && (addr & 0xff000000) == 0) {
			addr <<= 8;
			mask <<= 8;
		}
		return gen_host(cstate, addr, mask, proto, dir, q.addr);

	case Q_DEFAULT:
	case Q_HOST:
		if (proto == Q_LINK) {
			switch (cstate->linktype) {

			case DLT_EN10MB:
			case DLT_NETANALYZER:
			case DLT_NETANALYZER_TRANSPARENT:
				eaddr = pcap_ether_hostton(name);
				if (eaddr == NULL)
					bpf_error(cstate,
					    "unknown ether host '%s'", name);
				tmp = gen_prevlinkhdr_check(cstate);
				b = gen_ehostop(cstate, eaddr, dir);
				if (tmp != NULL)
					gen_and(tmp, b);
				free(eaddr);
				return b;

			case DLT_FDDI:
				eaddr = pcap_ether_hostton(name);
				if (eaddr == NULL)
					bpf_error(cstate,
					    "unknown FDDI host '%s'", name);
				b = gen_fhostop(cstate, eaddr, dir);
				free(eaddr);
				return b;

			case DLT_IEEE802:
				eaddr = pcap_ether_hostton(name);
				if (eaddr == NULL)
					bpf_error(cstate,
					    "unknown token ring host '%s'", name);
				b = gen_thostop(cstate, eaddr, dir);
				free(eaddr);
				return b;

			case DLT_IEEE802_11:
			case DLT_PRISM_HEADER:
			case DLT_IEEE802_11_RADIO_AVS:
			case DLT_IEEE802_11_RADIO:
			case DLT_PPI:
				eaddr = pcap_ether_hostton(name);
				if (eaddr == NULL)
					bpf_error(cstate,
					    "unknown 802.11 host '%s'", name);
				b = gen_wlanhostop(cstate, eaddr, dir);
				free(eaddr);
				return b;

			case DLT_IP_OVER_FC:
				eaddr = pcap_ether_hostton(name);
				if (eaddr == NULL)
					bpf_error(cstate,
					    "unknown Fibre Channel host '%s'", name);
				b = gen_ipfchostop(cstate, eaddr, dir);
				free(eaddr);
				return b;
			}

			bpf_error(cstate, "only ethernet/FDDI/token ring/802.11/ATM LANE/Fibre Channel supports link-level host name");
		} else if (proto == Q_DECNET) {
			unsigned short dn_addr;

			if (!__pcap_nametodnaddr(name, &dn_addr)) {
#ifdef	DECNETLIB
				bpf_error(cstate, "unknown decnet host name '%s'\n", name);
#else
				bpf_error(cstate, "decnet name support not included, '%s' cannot be translated\n",
					name);
#endif
			}
			/*
			 * I don't think DECNET hosts can be multihomed, so
			 * there is no need to build up a list of addresses
			 */
			return (gen_host(cstate, dn_addr, 0, proto, dir, q.addr));
		} else {
#ifdef INET6
			memset(&mask128, 0xff, sizeof(mask128));
#endif
			res0 = res = pcap_nametoaddrinfo(name);
			if (res == NULL)
				bpf_error(cstate, "unknown host '%s'", name);
			cstate->ai = res;
			b = tmp = NULL;
			tproto = proto;
#ifdef INET6
			tproto6 = proto;
#endif
			if (cstate->off_linktype.constant_part == OFFSET_NOT_SET &&
			    tproto == Q_DEFAULT) {
				tproto = Q_IP;
#ifdef INET6
				tproto6 = Q_IPV6;
#endif
			}
			for (res = res0; res; res = res->ai_next) {
				switch (res->ai_family) {
				case AF_INET:
#ifdef INET6
					if (tproto == Q_IPV6)
						continue;
#endif

					sin4 = (struct sockaddr_in *)
						res->ai_addr;
					tmp = gen_host(cstate, ntohl(sin4->sin_addr.s_addr),
						0xffffffff, tproto, dir, q.addr);
					break;
#ifdef INET6
				case AF_INET6:
					if (tproto6 == Q_IP)
						continue;

					sin6 = (struct sockaddr_in6 *)
						res->ai_addr;
					tmp = gen_host6(cstate, &sin6->sin6_addr,
						&mask128, tproto6, dir, q.addr);
					break;
#endif
				default:
					continue;
				}
				if (b)
					gen_or(b, tmp);
				b = tmp;
			}
			cstate->ai = NULL;
			freeaddrinfo(res0);
			if (b == NULL) {
				bpf_error(cstate, "unknown host '%s'%s", name,
				    (proto == Q_DEFAULT)
					? ""
					: " for specified address family");
			}
			return b;
		}

	case Q_PORT:
		if (proto != Q_DEFAULT &&
		    proto != Q_UDP && proto != Q_TCP && proto != Q_SCTP)
			bpf_error(cstate, "illegal qualifier of 'port'");
		if (pcap_nametoport(name, &port, &real_proto) == 0)
			bpf_error(cstate, "unknown port '%s'", name);
		if (proto == Q_UDP) {
			if (real_proto == IPPROTO_TCP)
				bpf_error(cstate, "port '%s' is tcp", name);
			else if (real_proto == IPPROTO_SCTP)
				bpf_error(cstate, "port '%s' is sctp", name);
			else
				/* override PROTO_UNDEF */
				real_proto = IPPROTO_UDP;
		}
		if (proto == Q_TCP) {
			if (real_proto == IPPROTO_UDP)
				bpf_error(cstate, "port '%s' is udp", name);

			else if (real_proto == IPPROTO_SCTP)
				bpf_error(cstate, "port '%s' is sctp", name);
			else
				/* override PROTO_UNDEF */
				real_proto = IPPROTO_TCP;
		}
		if (proto == Q_SCTP) {
			if (real_proto == IPPROTO_UDP)
				bpf_error(cstate, "port '%s' is udp", name);

			else if (real_proto == IPPROTO_TCP)
				bpf_error(cstate, "port '%s' is tcp", name);
			else
				/* override PROTO_UNDEF */
				real_proto = IPPROTO_SCTP;
		}
		if (port < 0)
			bpf_error(cstate, "illegal port number %d < 0", port);
		if (port > 65535)
			bpf_error(cstate, "illegal port number %d > 65535", port);
		b = gen_port(cstate, port, real_proto, dir);
		gen_or(gen_port6(cstate, port, real_proto, dir), b);
		return b;

	case Q_PORTRANGE:
		if (proto != Q_DEFAULT &&
		    proto != Q_UDP && proto != Q_TCP && proto != Q_SCTP)
			bpf_error(cstate, "illegal qualifier of 'portrange'");
		if (pcap_nametoportrange(name, &port1, &port2, &real_proto) == 0)
			bpf_error(cstate, "unknown port in range '%s'", name);
		if (proto == Q_UDP) {
			if (real_proto == IPPROTO_TCP)
				bpf_error(cstate, "port in range '%s' is tcp", name);
			else if (real_proto == IPPROTO_SCTP)
				bpf_error(cstate, "port in range '%s' is sctp", name);
			else
				/* override PROTO_UNDEF */
				real_proto = IPPROTO_UDP;
		}
		if (proto == Q_TCP) {
			if (real_proto == IPPROTO_UDP)
				bpf_error(cstate, "port in range '%s' is udp", name);
			else if (real_proto == IPPROTO_SCTP)
				bpf_error(cstate, "port in range '%s' is sctp", name);
			else
				/* override PROTO_UNDEF */
				real_proto = IPPROTO_TCP;
		}
		if (proto == Q_SCTP) {
			if (real_proto == IPPROTO_UDP)
				bpf_error(cstate, "port in range '%s' is udp", name);
			else if (real_proto == IPPROTO_TCP)
				bpf_error(cstate, "port in range '%s' is tcp", name);
			else
				/* override PROTO_UNDEF */
				real_proto = IPPROTO_SCTP;
		}
		if (port1 < 0)
			bpf_error(cstate, "illegal port number %d < 0", port1);
		if (port1 > 65535)
			bpf_error(cstate, "illegal port number %d > 65535", port1);
		if (port2 < 0)
			bpf_error(cstate, "illegal port number %d < 0", port2);
		if (port2 > 65535)
			bpf_error(cstate, "illegal port number %d > 65535", port2);

		b = gen_portrange(cstate, port1, port2, real_proto, dir);
		gen_or(gen_portrange6(cstate, port1, port2, real_proto, dir), b);
		return b;

	case Q_GATEWAY:
#ifndef INET6
		eaddr = pcap_ether_hostton(name);
		if (eaddr == NULL)
			bpf_error(cstate, "unknown ether host: %s", name);

		res = pcap_nametoaddrinfo(name);
		cstate->ai = res;
		if (res == NULL)
			bpf_error(cstate, "unknown host '%s'", name);
		b = gen_gateway(cstate, eaddr, res, proto, dir);
		cstate->ai = NULL;
		freeaddrinfo(res);
		if (b == NULL)
			bpf_error(cstate, "unknown host '%s'", name);
		return b;
#else
		bpf_error(cstate, "'gateway' not supported in this configuration");
#endif /*INET6*/

	case Q_PROTO:
		real_proto = lookup_proto(cstate, name, proto);
		if (real_proto >= 0)
			return gen_proto(cstate, real_proto, proto, dir);
		else
			bpf_error(cstate, "unknown protocol: %s", name);

	case Q_PROTOCHAIN:
		real_proto = lookup_proto(cstate, name, proto);
		if (real_proto >= 0)
			return gen_protochain(cstate, real_proto, proto, dir);
		else
			bpf_error(cstate, "unknown protocol: %s", name);

	case Q_UNDEF:
		syntax(cstate);
		/* NOTREACHED */
	}
	abort();
	/* NOTREACHED */
}