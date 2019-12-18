#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct udphdr {int uh_sport; int uh_dport; } ;
struct tcphdr {int th_sport; int th_dport; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_p; int ip_hl; TYPE_2__ ip_dst; TYPE_1__ ip_src; } ;

/* Variables and functions */
#define  IPPROTO_ESP 135 
#define  IPPROTO_GRE 134 
#define  IPPROTO_ICMP 133 
#define  IPPROTO_IGMP 132 
#define  IPPROTO_IPIP 131 
#define  IPPROTO_PIM 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  decode_gre_hash (int*,int,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  sym_hash_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
decode_ip_n_hash(struct ip *iph, uint8_t hash_split, uint8_t seed)
{
	uint32_t rc = 0;

	if (hash_split == 2) {
		rc = sym_hash_fn(ntohl(iph->ip_src.s_addr),
			ntohl(iph->ip_dst.s_addr),
			ntohs(0xFFFD) + seed,
			ntohs(0xFFFE) + seed);
	} else {
		struct tcphdr *tcph = NULL;
		struct udphdr *udph = NULL;

		switch (iph->ip_p) {
		case IPPROTO_TCP:
			tcph = (struct tcphdr *)((uint8_t *)iph + (iph->ip_hl<<2));
			rc = sym_hash_fn(ntohl(iph->ip_src.s_addr),
					 ntohl(iph->ip_dst.s_addr),
					 ntohs(tcph->th_sport) + seed,
					 ntohs(tcph->th_dport) + seed);
			break;
		case IPPROTO_UDP:
			udph = (struct udphdr *)((uint8_t *)iph + (iph->ip_hl<<2));
			rc = sym_hash_fn(ntohl(iph->ip_src.s_addr),
					 ntohl(iph->ip_dst.s_addr),
					 ntohs(udph->uh_sport) + seed,
					 ntohs(udph->uh_dport) + seed);
			break;
		case IPPROTO_IPIP:
			/* tunneling */
			rc = decode_ip_n_hash((struct ip *)((uint8_t *)iph + (iph->ip_hl<<2)),
					      hash_split, seed);
			break;
		case IPPROTO_GRE:
			rc = decode_gre_hash((uint8_t *)iph + (iph->ip_hl<<2),
					hash_split, seed);
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
			rc = sym_hash_fn(ntohl(iph->ip_src.s_addr),
					 ntohl(iph->ip_dst.s_addr),
					 ntohs(0xFFFD) + seed,
					 ntohs(0xFFFE) + seed);
			break;
		}
	}
	return rc;
}