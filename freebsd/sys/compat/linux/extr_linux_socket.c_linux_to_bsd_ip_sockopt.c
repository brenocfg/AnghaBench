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
 int IP_ADD_MEMBERSHIP ; 
 int IP_DROP_MEMBERSHIP ; 
 int IP_HDRINCL ; 
 int IP_MULTICAST_IF ; 
 int IP_MULTICAST_LOOP ; 
 int IP_MULTICAST_TTL ; 
 int IP_OPTIONS ; 
 int IP_TOS ; 
 int IP_TTL ; 
#define  LINUX_IP_ADD_MEMBERSHIP 136 
#define  LINUX_IP_DROP_MEMBERSHIP 135 
#define  LINUX_IP_HDRINCL 134 
#define  LINUX_IP_MULTICAST_IF 133 
#define  LINUX_IP_MULTICAST_LOOP 132 
#define  LINUX_IP_MULTICAST_TTL 131 
#define  LINUX_IP_OPTIONS 130 
#define  LINUX_IP_TOS 129 
#define  LINUX_IP_TTL 128 

__attribute__((used)) static int
linux_to_bsd_ip_sockopt(int opt)
{

	switch (opt) {
	case LINUX_IP_TOS:
		return (IP_TOS);
	case LINUX_IP_TTL:
		return (IP_TTL);
	case LINUX_IP_OPTIONS:
		return (IP_OPTIONS);
	case LINUX_IP_MULTICAST_IF:
		return (IP_MULTICAST_IF);
	case LINUX_IP_MULTICAST_TTL:
		return (IP_MULTICAST_TTL);
	case LINUX_IP_MULTICAST_LOOP:
		return (IP_MULTICAST_LOOP);
	case LINUX_IP_ADD_MEMBERSHIP:
		return (IP_ADD_MEMBERSHIP);
	case LINUX_IP_DROP_MEMBERSHIP:
		return (IP_DROP_MEMBERSHIP);
	case LINUX_IP_HDRINCL:
		return (IP_HDRINCL);
	}
	return (-1);
}