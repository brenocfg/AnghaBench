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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vlanhdr {int /*<<< orphan*/  proto; } ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
struct ether_header {int dummy; } ;

/* Variables and functions */
#define  ETHERTYPE_ARP 130 
#define  ETHERTYPE_IP 129 
#define  ETHERTYPE_IPV6 128 
 int /*<<< orphan*/  decode_ip_n_hash (struct ip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_ipv6_n_hash (struct ip6_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_others_n_hash (struct ether_header*,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
decode_vlan_n_hash(struct ether_header *ethh, uint8_t hash_split, uint8_t seed)
{
	uint32_t rc = 0;
	struct vlanhdr *vhdr = (struct vlanhdr *)(ethh + 1);

	switch (ntohs(vhdr->proto)) {
	case ETHERTYPE_IP:
		rc = decode_ip_n_hash((struct ip *)(vhdr + 1),
				      hash_split, seed);
		break;
	case ETHERTYPE_IPV6:
		rc = decode_ipv6_n_hash((struct ip6_hdr *)(vhdr + 1),
					hash_split, seed);
		break;
	case ETHERTYPE_ARP:
	default:
		/* others */
		rc = decode_others_n_hash(ethh, seed);
		break;
	}
	return rc;
}