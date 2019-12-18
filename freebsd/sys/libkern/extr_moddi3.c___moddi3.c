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
 int /*<<< orphan*/  __qdivrem (scalar_t__,scalar_t__,scalar_t__*) ; 

quad_t
__moddi3(quad_t a, quad_t b)
{
	u_quad_t ua, ub, ur;
	int neg;

	if (a < 0)
		ua = -(u_quad_t)a, neg = 1;
	else
		ua = a, neg = 0;
	if (b < 0)
		ub = -(u_quad_t)b;
	else
		ub = b;
	(void)__qdivrem(ua, ub, &ur);
	return (neg ? -ur : ur);
}