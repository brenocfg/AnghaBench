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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;

/* Variables and functions */
#define  ETHERTYPE_IP 129 
#define  ETHERTYPE_IPV6 128 
 int /*<<< orphan*/  decode_ip_n_hash (struct ip*,int,int) ; 
 int /*<<< orphan*/  decode_ipv6_n_hash (struct ip6_hdr*,int,int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  pkt_hdr_hash (int const*,int,int) ; 

__attribute__((used)) static uint32_t
decode_gre_hash(const uint8_t *grehdr, uint8_t hash_split, uint8_t seed)
{
	uint32_t rc = 0;
	int len = 4 + 2 * (!!(*grehdr & 1) + /* Checksum */
			   !!(*grehdr & 2) + /* Routing */
			   !!(*grehdr & 4) + /* Key */
			   !!(*grehdr & 8)); /* Sequence Number */
	uint16_t proto = ntohs(*(uint16_t *)(void *)(grehdr + 2));

	switch (proto) {
	case ETHERTYPE_IP:
		rc = decode_ip_n_hash((struct ip *)(grehdr + len),
				      hash_split, seed);
		break;
	case ETHERTYPE_IPV6:
		rc = decode_ipv6_n_hash((struct ip6_hdr *)(grehdr + len),
					hash_split, seed);
		break;
	case 0x6558: /* Transparent Ethernet Bridging */
		rc = pkt_hdr_hash(grehdr + len, hash_split, seed);
		break;
	default:
		/* others */
		break;
	}
	return rc;
}