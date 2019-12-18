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
#define  M_HASHTYPE_RSS_IPV4 133 
#define  M_HASHTYPE_RSS_IPV6 132 
#define  M_HASHTYPE_RSS_TCP_IPV4 131 
#define  M_HASHTYPE_RSS_TCP_IPV6 130 
#define  M_HASHTYPE_RSS_UDP_IPV4 129 
#define  M_HASHTYPE_RSS_UDP_IPV6 128 
 int rss_getbucket (int) ; 

int
rss_hash2bucket(uint32_t hash_val, uint32_t hash_type, uint32_t *bucket_id)
{

	switch (hash_type) {
	case M_HASHTYPE_RSS_IPV4:
	case M_HASHTYPE_RSS_TCP_IPV4:
	case M_HASHTYPE_RSS_UDP_IPV4:
	case M_HASHTYPE_RSS_IPV6:
	case M_HASHTYPE_RSS_TCP_IPV6:
	case M_HASHTYPE_RSS_UDP_IPV6:
		*bucket_id = rss_getbucket(hash_val);
		return (0);
	default:
		return (-1);
	}
}