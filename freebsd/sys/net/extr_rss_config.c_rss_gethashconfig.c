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
typedef  int u_int ;

/* Variables and functions */
 int RSS_HASHTYPE_RSS_IPV4 ; 
 int RSS_HASHTYPE_RSS_IPV6 ; 
 int RSS_HASHTYPE_RSS_IPV6_EX ; 
 int RSS_HASHTYPE_RSS_TCP_IPV4 ; 
 int RSS_HASHTYPE_RSS_TCP_IPV6 ; 
 int RSS_HASHTYPE_RSS_TCP_IPV6_EX ; 
 int RSS_HASHTYPE_RSS_UDP_IPV4 ; 
 int RSS_HASHTYPE_RSS_UDP_IPV6 ; 
 int RSS_HASHTYPE_RSS_UDP_IPV6_EX ; 

inline u_int
rss_gethashconfig(void)
{

	/* Return 4-tuple for TCP; 2-tuple for others */
	/*
	 * UDP may fragment more often than TCP and thus we'll end up with
	 * NICs returning 2-tuple fragments.
	 * udp_init() and udplite_init() both currently initialise things
	 * as 2-tuple.
	 * So for now disable UDP 4-tuple hashing until all of the other
	 * pieces are in place.
	 */
	return (
	    RSS_HASHTYPE_RSS_IPV4
	|    RSS_HASHTYPE_RSS_TCP_IPV4
	|    RSS_HASHTYPE_RSS_IPV6
	|    RSS_HASHTYPE_RSS_TCP_IPV6
	|    RSS_HASHTYPE_RSS_IPV6_EX
	|    RSS_HASHTYPE_RSS_TCP_IPV6_EX
#if 0
	|    RSS_HASHTYPE_RSS_UDP_IPV4
	|    RSS_HASHTYPE_RSS_UDP_IPV6
	|    RSS_HASHTYPE_RSS_UDP_IPV6_EX
#endif
	);
}