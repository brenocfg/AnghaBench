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
typedef  int u_long ;

/* Variables and functions */
 int casueword (int volatile*,int,int*,int) ; 

u_long
casuword(volatile u_long *addr, u_long old, u_long new)
{
	int rv;
	u_long val;

	rv = casueword(addr, old, &val, new);
	return (rv == -1 ? -1 : val);
}