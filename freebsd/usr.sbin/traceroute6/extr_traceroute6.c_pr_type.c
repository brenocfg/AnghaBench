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
typedef  int u_char ;

/* Variables and functions */
#define  ICMP6_DST_UNREACH 141 
#define  ICMP6_ECHO_REPLY 140 
#define  ICMP6_ECHO_REQUEST 139 
#define  ICMP6_MEMBERSHIP_QUERY 138 
#define  ICMP6_MEMBERSHIP_REDUCTION 137 
#define  ICMP6_MEMBERSHIP_REPORT 136 
#define  ICMP6_PACKET_TOO_BIG 135 
#define  ICMP6_PARAM_PROB 134 
#define  ICMP6_TIME_EXCEEDED 133 
#define  ND_NEIGHBOR_ADVERT 132 
#define  ND_NEIGHBOR_SOLICIT 131 
#define  ND_REDIRECT 130 
#define  ND_ROUTER_ADVERT 129 
#define  ND_ROUTER_SOLICIT 128 

const char *
pr_type(int t0)
{
	u_char t = t0 & 0xff;
	const char *cp;

	switch (t) {
	case ICMP6_DST_UNREACH:
		cp = "Destination Unreachable";
		break;
	case ICMP6_PACKET_TOO_BIG:
		cp = "Packet Too Big";
		break;
	case ICMP6_TIME_EXCEEDED:
		cp = "Time Exceeded";
		break;
	case ICMP6_PARAM_PROB:
		cp = "Parameter Problem";
		break;
	case ICMP6_ECHO_REQUEST:
		cp = "Echo Request";
		break;
	case ICMP6_ECHO_REPLY:
		cp = "Echo Reply";
		break;
	case ICMP6_MEMBERSHIP_QUERY:
		cp = "Group Membership Query";
		break;
	case ICMP6_MEMBERSHIP_REPORT:
		cp = "Group Membership Report";
		break;
	case ICMP6_MEMBERSHIP_REDUCTION:
		cp = "Group Membership Reduction";
		break;
	case ND_ROUTER_SOLICIT:
		cp = "Router Solicitation";
		break;
	case ND_ROUTER_ADVERT:
		cp = "Router Advertisement";
		break;
	case ND_NEIGHBOR_SOLICIT:
		cp = "Neighbor Solicitation";
		break;
	case ND_NEIGHBOR_ADVERT:
		cp = "Neighbor Advertisement";
		break;
	case ND_REDIRECT:
		cp = "Redirect";
		break;
	default:
		cp = "Unknown";
		break;
	}
	return cp;
}