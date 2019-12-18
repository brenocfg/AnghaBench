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
typedef  int u32 ;

/* Variables and functions */
#define  E1000_RXDADV_RSSTYPE_IPV4 133 
#define  E1000_RXDADV_RSSTYPE_IPV4_TCP 132 
#define  E1000_RXDADV_RSSTYPE_IPV6 131 
#define  E1000_RXDADV_RSSTYPE_IPV6_EX 130 
#define  E1000_RXDADV_RSSTYPE_IPV6_TCP 129 
#define  E1000_RXDADV_RSSTYPE_IPV6_TCP_EX 128 
 int E1000_RXDADV_RSSTYPE_MASK ; 
 int M_HASHTYPE_OPAQUE ; 
 int M_HASHTYPE_RSS_IPV4 ; 
 int M_HASHTYPE_RSS_IPV6 ; 
 int M_HASHTYPE_RSS_IPV6_EX ; 
 int M_HASHTYPE_RSS_TCP_IPV4 ; 
 int M_HASHTYPE_RSS_TCP_IPV6 ; 
 int M_HASHTYPE_RSS_TCP_IPV6_EX ; 

__attribute__((used)) static int
em_determine_rsstype(u32 pkt_info)
{
	switch (pkt_info & E1000_RXDADV_RSSTYPE_MASK) {
	case E1000_RXDADV_RSSTYPE_IPV4_TCP:
		return M_HASHTYPE_RSS_TCP_IPV4;
	case E1000_RXDADV_RSSTYPE_IPV4:
		return M_HASHTYPE_RSS_IPV4;
	case E1000_RXDADV_RSSTYPE_IPV6_TCP:
		return M_HASHTYPE_RSS_TCP_IPV6;
	case E1000_RXDADV_RSSTYPE_IPV6_EX: 
		return M_HASHTYPE_RSS_IPV6_EX;
	case E1000_RXDADV_RSSTYPE_IPV6:
		return M_HASHTYPE_RSS_IPV6;
	case E1000_RXDADV_RSSTYPE_IPV6_TCP_EX:
		return M_HASHTYPE_RSS_TCP_IPV6_EX;
	default:
		return M_HASHTYPE_OPAQUE;
	}
}