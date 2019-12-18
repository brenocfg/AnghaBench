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
#define  ETHERTYPE_ATALK 135 
#define  ETHERTYPE_DN 134 
#define  ETHERTYPE_IP 133 
#define  ETHERTYPE_IPV6 132 
#define  ETHERTYPE_NS 131 
#define  LLCSAP_8021D 130 
#define  LLCSAP_IPX 129 
#define  LLCSAP_ISONS 128 
 int PPP_APPLE ; 
 int PPP_BRPDU ; 
 int PPP_DECNET ; 
 int PPP_IP ; 
 int PPP_IPV6 ; 
 int PPP_IPX ; 
 int PPP_NS ; 
 int PPP_OSI ; 

__attribute__((used)) static int
ethertype_to_ppptype(int proto)
{
	switch (proto) {

	case ETHERTYPE_IP:
		proto = PPP_IP;
		break;

	case ETHERTYPE_IPV6:
		proto = PPP_IPV6;
		break;

	case ETHERTYPE_DN:
		proto = PPP_DECNET;
		break;

	case ETHERTYPE_ATALK:
		proto = PPP_APPLE;
		break;

	case ETHERTYPE_NS:
		proto = PPP_NS;
		break;

	case LLCSAP_ISONS:
		proto = PPP_OSI;
		break;

	case LLCSAP_8021D:
		/*
		 * I'm assuming the "Bridging PDU"s that go
		 * over PPP are Spanning Tree Protocol
		 * Bridging PDUs.
		 */
		proto = PPP_BRPDU;
		break;

	case LLCSAP_IPX:
		proto = PPP_IPX;
		break;
	}
	return (proto);
}