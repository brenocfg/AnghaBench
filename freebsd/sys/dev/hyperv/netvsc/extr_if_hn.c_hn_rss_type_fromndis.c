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
typedef  int uint32_t ;

/* Variables and functions */
 int NDIS_HASH_IPV4 ; 
 int NDIS_HASH_IPV6 ; 
 int NDIS_HASH_IPV6_EX ; 
 int NDIS_HASH_TCP_IPV4 ; 
 int NDIS_HASH_TCP_IPV6 ; 
 int NDIS_HASH_TCP_IPV6_EX ; 
 int NDIS_HASH_UDP_IPV4_X ; 
 int RSS_TYPE_IPV4 ; 
 int RSS_TYPE_IPV6 ; 
 int RSS_TYPE_IPV6_EX ; 
 int RSS_TYPE_TCP_IPV4 ; 
 int RSS_TYPE_TCP_IPV6 ; 
 int RSS_TYPE_TCP_IPV6_EX ; 
 int RSS_TYPE_UDP_IPV4 ; 

__attribute__((used)) static uint32_t
hn_rss_type_fromndis(uint32_t rss_hash)
{
	uint32_t types = 0;

	if (rss_hash & NDIS_HASH_IPV4)
		types |= RSS_TYPE_IPV4;
	if (rss_hash & NDIS_HASH_TCP_IPV4)
		types |= RSS_TYPE_TCP_IPV4;
	if (rss_hash & NDIS_HASH_IPV6)
		types |= RSS_TYPE_IPV6;
	if (rss_hash & NDIS_HASH_IPV6_EX)
		types |= RSS_TYPE_IPV6_EX;
	if (rss_hash & NDIS_HASH_TCP_IPV6)
		types |= RSS_TYPE_TCP_IPV6;
	if (rss_hash & NDIS_HASH_TCP_IPV6_EX)
		types |= RSS_TYPE_TCP_IPV6_EX;
	if (rss_hash & NDIS_HASH_UDP_IPV4_X)
		types |= RSS_TYPE_UDP_IPV4;
	return (types);
}