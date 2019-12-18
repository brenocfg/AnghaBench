#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; } ;
struct in_ifaddr {scalar_t__ ia_subnetmask; scalar_t__ ia_subnet; TYPE_2__ ia_broadaddr; } ;
struct in_addr {scalar_t__ s_addr; } ;

/* Variables and functions */
 scalar_t__ IN_RFC3021_MASK ; 
 scalar_t__ ntohl (scalar_t__) ; 

int
in_ifaddr_broadcast(struct in_addr in, struct in_ifaddr *ia)
{

	return ((in.s_addr == ia->ia_broadaddr.sin_addr.s_addr ||
	     /*
	      * Check for old-style (host 0) broadcast, but
	      * taking into account that RFC 3021 obsoletes it.
	      */
	    (ia->ia_subnetmask != IN_RFC3021_MASK &&
	    ntohl(in.s_addr) == ia->ia_subnet)) &&
	     /*
	      * Check for an all one subnetmask. These
	      * only exist when an interface gets a secondary
	      * address.
	      */
	    ia->ia_subnetmask != (u_long)0xffffffff);
}