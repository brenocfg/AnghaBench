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
typedef  scalar_t__ u_quad_t ;
typedef  scalar_t__ quad_t ;

/* Variables and functions */
 scalar_t__ __qdivrem (scalar_t__,scalar_t__,scalar_t__*) ; 

quad_t
__divdi3(quad_t a, quad_t b)
{
	u_quad_t ua, ub, uq;
	int neg;

	if (a < 0)
		ua = -(u_quad_t)a, neg = 1;
	else
		ua = a, neg = 0;
	if (b < 0)
		ub = -(u_quad_t)b, neg ^= 1;
	else
		ub = b;
	uq = __qdivrem(ua, ub, (u_quad_t *)0);
	return (neg ? -uq : uq);
}