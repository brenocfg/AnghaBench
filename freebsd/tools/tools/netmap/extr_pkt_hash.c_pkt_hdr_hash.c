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
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
struct ether_header {int /*<<< orphan*/  ether_type; } ;

/* Variables and functions */
#define  ETHERTYPE_ARP 131 
#define  ETHERTYPE_IP 130 
#define  ETHERTYPE_IPV6 129 
#define  ETHERTYPE_VLAN 128 
 int /*<<< orphan*/  decode_ip_n_hash (struct ip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_ipv6_n_hash (struct ip6_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_others_n_hash (struct ether_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_vlan_n_hash (struct ether_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

uint32_t
pkt_hdr_hash(const unsigned char *buffer, uint8_t hash_split, uint8_t seed)
{
	uint32_t rc = 0;
	struct ether_header *ethh = (struct ether_header *)buffer;

	switch (ntohs(ethh->ether_type)) {
	case ETHERTYPE_IP:
		rc = decode_ip_n_hash((struct ip *)(ethh + 1),
				      hash_split, seed);
		break;
	case ETHERTYPE_IPV6:
		rc = decode_ipv6_n_hash((struct ip6_hdr *)(ethh + 1),
					hash_split, seed);
		break;
	case ETHERTYPE_VLAN:
		rc = decode_vlan_n_hash(ethh, hash_split, seed);
		break;
	case ETHERTYPE_ARP:
	default:
		/* others */
		rc = decode_others_n_hash(ethh, seed);
		break;
	}

	return rc;
}