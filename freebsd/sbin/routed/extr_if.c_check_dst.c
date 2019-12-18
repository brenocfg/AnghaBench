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
typedef  int naddr ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (int) ; 
 int IN_CLASSA_NSHIFT ; 
 scalar_t__ IN_CLASSB (int) ; 
 scalar_t__ IN_CLASSC (int) ; 
 int IN_LOOPBACKNET ; 
 int ntohl (int) ; 

int					/* 0=bad */
check_dst(naddr addr)
{
	addr = ntohl(addr);

	if (IN_CLASSA(addr)) {
		if (addr == 0)
			return 1;	/* default */

		addr >>= IN_CLASSA_NSHIFT;
		return (addr != 0 && addr != IN_LOOPBACKNET);
	}

	return (IN_CLASSB(addr) || IN_CLASSC(addr));
}