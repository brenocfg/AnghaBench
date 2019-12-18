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
typedef  long u_long ;

/* Variables and functions */
 long casuword64_int (long volatile*,long,long) ; 

u_long
casuword(volatile u_long *p, u_long oldval, u_long newval)
{
	u_long ret;

	ret = casuword64_int(p, oldval, newval);
	if (ret != -1L)
		ret = ret != oldval;
	return (ret);
}