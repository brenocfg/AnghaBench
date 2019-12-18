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
typedef  int u8 ;
typedef  int u32 ;
struct sfe_ipv6_addr {int* addr; } ;
struct net_device {int dummy; } ;
typedef  int __be16 ;

/* Variables and functions */
 int SFE_IPV6_CONNECTION_HASH_MASK ; 
 int SFE_IPV6_CONNECTION_HASH_SHIFT ; 
 int ntohs (int) ; 

__attribute__((used)) static inline unsigned int sfe_ipv6_get_connection_match_hash(struct net_device *dev, u8 protocol,
							      struct sfe_ipv6_addr *src_ip, __be16 src_port,
							      struct sfe_ipv6_addr *dest_ip, __be16 dest_port)
{
	u32 idx, hash = 0;
	size_t dev_addr = (size_t)dev;

	for (idx = 0; idx < 4; idx++) {
		hash ^= src_ip->addr[idx] ^ dest_ip->addr[idx];
	}
	hash = ((u32)dev_addr) ^ hash ^ protocol ^ ntohs(src_port ^ dest_port);
	return ((hash >> SFE_IPV6_CONNECTION_HASH_SHIFT) ^ hash) & SFE_IPV6_CONNECTION_HASH_MASK;
}