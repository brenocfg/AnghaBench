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
typedef  int u16 ;

/* Variables and functions */
#define  IXGBE_RXDADV_RSSTYPE_IPV4 136 
#define  IXGBE_RXDADV_RSSTYPE_IPV4_TCP 135 
#define  IXGBE_RXDADV_RSSTYPE_IPV4_UDP 134 
#define  IXGBE_RXDADV_RSSTYPE_IPV6 133 
#define  IXGBE_RXDADV_RSSTYPE_IPV6_EX 132 
#define  IXGBE_RXDADV_RSSTYPE_IPV6_TCP 131 
#define  IXGBE_RXDADV_RSSTYPE_IPV6_TCP_EX 130 
#define  IXGBE_RXDADV_RSSTYPE_IPV6_UDP 129 
#define  IXGBE_RXDADV_RSSTYPE_IPV6_UDP_EX 128 
 int IXGBE_RXDADV_RSSTYPE_MASK ; 
 int M_HASHTYPE_OPAQUE ; 
 int M_HASHTYPE_RSS_IPV4 ; 
 int M_HASHTYPE_RSS_IPV6 ; 
 int M_HASHTYPE_RSS_IPV6_EX ; 
 int M_HASHTYPE_RSS_TCP_IPV4 ; 
 int M_HASHTYPE_RSS_TCP_IPV6 ; 
 int M_HASHTYPE_RSS_TCP_IPV6_EX ; 
 int M_HASHTYPE_RSS_UDP_IPV4 ; 
 int M_HASHTYPE_RSS_UDP_IPV6 ; 
 int M_HASHTYPE_RSS_UDP_IPV6_EX ; 

__attribute__((used)) static int
ixgbe_determine_rsstype(u16 pkt_info)
{
	switch (pkt_info & IXGBE_RXDADV_RSSTYPE_MASK) {
	case IXGBE_RXDADV_RSSTYPE_IPV4_TCP:
		return M_HASHTYPE_RSS_TCP_IPV4;
	case IXGBE_RXDADV_RSSTYPE_IPV4:
		return M_HASHTYPE_RSS_IPV4;
	case IXGBE_RXDADV_RSSTYPE_IPV6_TCP:
		return M_HASHTYPE_RSS_TCP_IPV6;
	case IXGBE_RXDADV_RSSTYPE_IPV6_EX:
		return M_HASHTYPE_RSS_IPV6_EX;
	case IXGBE_RXDADV_RSSTYPE_IPV6:
		return M_HASHTYPE_RSS_IPV6;
	case IXGBE_RXDADV_RSSTYPE_IPV6_TCP_EX:
		return M_HASHTYPE_RSS_TCP_IPV6_EX;
	case IXGBE_RXDADV_RSSTYPE_IPV4_UDP:
		return M_HASHTYPE_RSS_UDP_IPV4;
	case IXGBE_RXDADV_RSSTYPE_IPV6_UDP:
		return M_HASHTYPE_RSS_UDP_IPV6;
	case IXGBE_RXDADV_RSSTYPE_IPV6_UDP_EX:
		return M_HASHTYPE_RSS_UDP_IPV6_EX;
	default:
		return M_HASHTYPE_OPAQUE;
	}
}