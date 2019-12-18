#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct udphdr {int uh_sport; int uh_dport; } ;
struct tcphdr {int th_sport; int th_dport; } ;
struct TYPE_7__ {int ip6_un1_nxt; } ;
struct TYPE_8__ {TYPE_3__ ip6_un1; } ;
struct TYPE_6__ {int* s6_addr; } ;
struct TYPE_5__ {int* s6_addr; } ;
struct ip6_hdr {TYPE_4__ ip6_ctlun; TYPE_2__ ip6_dst; TYPE_1__ ip6_src; } ;
struct ip {int dummy; } ;

/* Variables and functions */
#define  IPPROTO_ESP 136 
#define  IPPROTO_GRE 135 
#define  IPPROTO_ICMP 134 
#define  IPPROTO_IGMP 133 
#define  IPPROTO_IPIP 132 
#define  IPPROTO_IPV6 131 
#define  IPPROTO_PIM 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int decode_gre_hash (int*,int,int) ; 
 int decode_ip_n_hash (struct ip*,int,int) ; 
 int /*<<< orphan*/  ntohl (int) ; 
 int ntohs (int) ; 
 int sym_hash_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
decode_ipv6_n_hash(struct ip6_hdr *ipv6h, uint8_t hash_split, uint8_t seed)
{
	uint32_t saddr, daddr;
	uint32_t rc = 0;

	/* Get only the first 4 octets */
	saddr = ipv6h->ip6_src.s6_addr[0] |
		(ipv6h->ip6_src.s6_addr[1] << 8) |
		(ipv6h->ip6_src.s6_addr[2] << 16) |
		(ipv6h->ip6_src.s6_addr[3] << 24);
	daddr = ipv6h->ip6_dst.s6_addr[0] |
		(ipv6h->ip6_dst.s6_addr[1] << 8) |
		(ipv6h->ip6_dst.s6_addr[2] << 16) |
		(ipv6h->ip6_dst.s6_addr[3] << 24);

	if (hash_split == 2) {
		rc = sym_hash_fn(ntohl(saddr),
				 ntohl(daddr),
				 ntohs(0xFFFD) + seed,
				 ntohs(0xFFFE) + seed);
	} else {
		struct tcphdr *tcph = NULL;
		struct udphdr *udph = NULL;

		switch(ntohs(ipv6h->ip6_ctlun.ip6_un1.ip6_un1_nxt)) {
		case IPPROTO_TCP:
			tcph = (struct tcphdr *)(ipv6h + 1);
			rc = sym_hash_fn(ntohl(saddr),
					 ntohl(daddr),
					 ntohs(tcph->th_sport) + seed,
					 ntohs(tcph->th_dport) + seed);
			break;
		case IPPROTO_UDP:
			udph = (struct udphdr *)(ipv6h + 1);
			rc = sym_hash_fn(ntohl(saddr),
					 ntohl(daddr),
					 ntohs(udph->uh_sport) + seed,
					 ntohs(udph->uh_dport) + seed);
			break;
		case IPPROTO_IPIP:
			/* tunneling */
			rc = decode_ip_n_hash((struct ip *)(ipv6h + 1),
					      hash_split, seed);
			break;
		case IPPROTO_IPV6:
			/* tunneling */
			rc = decode_ipv6_n_hash((struct ip6_hdr *)(ipv6h + 1),
						hash_split, seed);
			break;
		case IPPROTO_GRE:
			rc = decode_gre_hash((uint8_t *)(ipv6h + 1), hash_split, seed);
			break;
		case IPPROTO_ICMP:
		case IPPROTO_ESP:
		case IPPROTO_PIM:
		case IPPROTO_IGMP:
		default:
			/*
			 ** the hash strength (although weaker but) should still hold
			 ** even with 2 fields
			 **/
			rc = sym_hash_fn(ntohl(saddr),
					 ntohl(daddr),
					 ntohs(0xFFFD) + seed,
					 ntohs(0xFFFE) + seed);
		}
	}
	return rc;
}