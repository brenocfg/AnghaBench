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

/* Variables and functions */
 int IPV6_CHECKSUM ; 
 int IPV6_DONTFRAG ; 
 int IPV6_DSTOPTS ; 
 int IPV6_HOPLIMIT ; 
 int IPV6_HOPOPTS ; 
 int IPV6_JOIN_GROUP ; 
 int IPV6_LEAVE_GROUP ; 
 int IPV6_MULTICAST_HOPS ; 
 int IPV6_MULTICAST_IF ; 
 int IPV6_MULTICAST_LOOP ; 
 int IPV6_NEXTHOP ; 
 int IPV6_PATHMTU ; 
 int IPV6_PKTINFO ; 
 int IPV6_RECVDSTOPTS ; 
 int IPV6_RECVHOPLIMIT ; 
 int IPV6_RECVHOPOPTS ; 
 int IPV6_RECVPATHMTU ; 
 int IPV6_RECVPKTINFO ; 
 int IPV6_RECVRTHDR ; 
 int IPV6_RTHDR ; 
 int IPV6_RTHDRDSTOPTS ; 
 int IPV6_UNICAST_HOPS ; 
 int IPV6_V6ONLY ; 
#define  LINUX_IPV6_ADD_MEMBERSHIP 150 
#define  LINUX_IPV6_CHECKSUM 149 
#define  LINUX_IPV6_DONTFRAG 148 
#define  LINUX_IPV6_DROP_MEMBERSHIP 147 
#define  LINUX_IPV6_DSTOPTS 146 
#define  LINUX_IPV6_HOPLIMIT 145 
#define  LINUX_IPV6_HOPOPTS 144 
#define  LINUX_IPV6_MULTICAST_HOPS 143 
#define  LINUX_IPV6_MULTICAST_IF 142 
#define  LINUX_IPV6_MULTICAST_LOOP 141 
#define  LINUX_IPV6_NEXTHOP 140 
#define  LINUX_IPV6_PATHMTU 139 
#define  LINUX_IPV6_PKTINFO 138 
#define  LINUX_IPV6_RECVDSTOPTS 137 
#define  LINUX_IPV6_RECVHOPLIMIT 136 
#define  LINUX_IPV6_RECVHOPOPTS 135 
#define  LINUX_IPV6_RECVPATHMTU 134 
#define  LINUX_IPV6_RECVPKTINFO 133 
#define  LINUX_IPV6_RECVRTHDR 132 
#define  LINUX_IPV6_RTHDR 131 
#define  LINUX_IPV6_RTHDRDSTOPTS 130 
#define  LINUX_IPV6_UNICAST_HOPS 129 
#define  LINUX_IPV6_V6ONLY 128 

__attribute__((used)) static int
linux_to_bsd_ip6_sockopt(int opt)
{

	switch (opt) {
	case LINUX_IPV6_NEXTHOP:
		return (IPV6_NEXTHOP);
	case LINUX_IPV6_UNICAST_HOPS:
		return (IPV6_UNICAST_HOPS);
	case LINUX_IPV6_MULTICAST_IF:
		return (IPV6_MULTICAST_IF);
	case LINUX_IPV6_MULTICAST_HOPS:
		return (IPV6_MULTICAST_HOPS);
	case LINUX_IPV6_MULTICAST_LOOP:
		return (IPV6_MULTICAST_LOOP);
	case LINUX_IPV6_ADD_MEMBERSHIP:
		return (IPV6_JOIN_GROUP);
	case LINUX_IPV6_DROP_MEMBERSHIP:
		return (IPV6_LEAVE_GROUP);
	case LINUX_IPV6_V6ONLY:
		return (IPV6_V6ONLY);
	case LINUX_IPV6_DONTFRAG:
		return (IPV6_DONTFRAG);
#if 0
	case LINUX_IPV6_CHECKSUM:
		return (IPV6_CHECKSUM);
	case LINUX_IPV6_RECVPKTINFO:
		return (IPV6_RECVPKTINFO);
	case LINUX_IPV6_PKTINFO:
		return (IPV6_PKTINFO);
	case LINUX_IPV6_RECVHOPLIMIT:
		return (IPV6_RECVHOPLIMIT);
	case LINUX_IPV6_HOPLIMIT:
		return (IPV6_HOPLIMIT);
	case LINUX_IPV6_RECVHOPOPTS:
		return (IPV6_RECVHOPOPTS);
	case LINUX_IPV6_HOPOPTS:
		return (IPV6_HOPOPTS);
	case LINUX_IPV6_RTHDRDSTOPTS:
		return (IPV6_RTHDRDSTOPTS);
	case LINUX_IPV6_RECVRTHDR:
		return (IPV6_RECVRTHDR);
	case LINUX_IPV6_RTHDR:
		return (IPV6_RTHDR);
	case LINUX_IPV6_RECVDSTOPTS:
		return (IPV6_RECVDSTOPTS);
	case LINUX_IPV6_DSTOPTS:
		return (IPV6_DSTOPTS);
	case LINUX_IPV6_RECVPATHMTU:
		return (IPV6_RECVPATHMTU);
	case LINUX_IPV6_PATHMTU:
		return (IPV6_PATHMTU);
#endif
	}
	return (-1);
}