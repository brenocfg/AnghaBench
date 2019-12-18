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
union uu {scalar_t__ q; scalar_t__* ul; } ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ quad_t ;

/* Variables and functions */
 size_t H ; 
 scalar_t__ HHALF (scalar_t__) ; 
 size_t L ; 
 scalar_t__ LHALF (scalar_t__) ; 
 scalar_t__ LHUP (scalar_t__) ; 

__attribute__((used)) static quad_t
__lmulq(u_int u, u_int v)
{
	u_int u1, u0, v1, v0, udiff, vdiff, high, mid, low;
	u_int prodh, prodl, was;
	union uu prod;
	int neg;

	u1 = HHALF(u);
	u0 = LHALF(u);
	v1 = HHALF(v);
	v0 = LHALF(v);

	low = u0 * v0;

	/* This is the same small-number optimization as before. */
	if (u1 == 0 && v1 == 0)
		return (low);

	if (u1 >= u0)
		udiff = u1 - u0, neg = 0;
	else
		udiff = u0 - u1, neg = 1;
	if (v0 >= v1)
		vdiff = v0 - v1;
	else
		vdiff = v1 - v0, neg ^= 1;
	mid = udiff * vdiff;

	high = u1 * v1;

	/* prod = (high << 2N) + (high << N); */
	prodh = high + HHALF(high);
	prodl = LHUP(high);

	/* if (neg) prod -= mid << N; else prod += mid << N; */
	if (neg) {
		was = prodl;
		prodl -= LHUP(mid);
		prodh -= HHALF(mid) + (prodl > was);
	} else {
		was = prodl;
		prodl += LHUP(mid);
		prodh += HHALF(mid) + (prodl < was);
	}

	/* prod += low << N */
	was = prodl;
	prodl += LHUP(low);
	prodh += HHALF(low) + (prodl < was);
	/* ... + low; */
	if ((prodl += low) < low)
		prodh++;

	/* return 4N-bit product */
	prod.ul[H] = prodh;
	prod.ul[L] = prodl;
	return (prod.q);
}