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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (scalar_t__) ; 
 scalar_t__ IN_CLASSA_NET ; 
 scalar_t__ IN_CLASSB (scalar_t__) ; 
 scalar_t__ IN_CLASSB_NET ; 
 scalar_t__ IN_CLASSC_NET ; 
 scalar_t__ ntohl (scalar_t__) ; 

__attribute__((used)) static u_int
std_mask(u_int addr)			/* in network order */
{
	addr = ntohl(addr);		/* was a host, not a network */

	if (addr == 0)			/* default route has mask 0 */
		return 0;
	if (IN_CLASSA(addr))
		return IN_CLASSA_NET;
	if (IN_CLASSB(addr))
		return IN_CLASSB_NET;
	return IN_CLASSC_NET;
}