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
union uu {scalar_t__* ul; int /*<<< orphan*/  uq; } ;
typedef  int /*<<< orphan*/  u_quad_t ;

/* Variables and functions */
 size_t H ; 
 size_t L ; 
 int LONG_BITS ; 

double
__floatunsdidf(u_quad_t x)
{
	double d;
	union uu u;

	u.uq = x;
	d = (double)u.ul[H] * ((1 << (LONG_BITS - 2)) * 4.0);
	d += u.ul[L];
	return (d);
}