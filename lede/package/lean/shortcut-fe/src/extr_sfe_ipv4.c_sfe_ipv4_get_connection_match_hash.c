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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct net_device {int dummy; } ;
typedef  int __be32 ;
typedef  int __be16 ;

/* Variables and functions */
 unsigned int SFE_IPV4_CONNECTION_HASH_MASK ; 
 unsigned int SFE_IPV4_CONNECTION_HASH_SHIFT ; 
 unsigned int ntohl (int) ; 
 unsigned int ntohs (int) ; 

__attribute__((used)) static inline unsigned int sfe_ipv4_get_connection_match_hash(struct net_device *dev, u8 protocol,
							      __be32 src_ip, __be16 src_port,
							      __be32 dest_ip, __be16 dest_port)
{
	size_t dev_addr = (size_t)dev;
	u32 hash = ((u32)dev_addr) ^ ntohl(src_ip ^ dest_ip) ^ protocol ^ ntohs(src_port ^ dest_port);
	return ((hash >> SFE_IPV4_CONNECTION_HASH_SHIFT) ^ hash) & SFE_IPV4_CONNECTION_HASH_MASK;
}