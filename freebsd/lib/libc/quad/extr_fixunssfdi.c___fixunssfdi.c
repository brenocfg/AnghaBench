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
union uu {unsigned long* ul; float uq; } ;
typedef  float u_quad_t ;
typedef  unsigned long u_long ;

/* Variables and functions */
 size_t H ; 
 size_t L ; 
 double ONE ; 
 double ONE_HALF ; 
 double ULONG_MAX ; 
 float UQUAD_MAX ; 

u_quad_t
__fixunssfdi(float f)
{
	double x, toppart;
	union uu t;

	if (f < 0)
		return (UQUAD_MAX);	/* ??? should be 0?  ERANGE??? */
#ifdef notdef				/* this falls afoul of a GCC bug */
	if (f >= UQUAD_MAX)
		return (UQUAD_MAX);
#else					/* so we wire in 2^64-1 instead */
	if (f >= 18446744073709551615.0)
		return (UQUAD_MAX);
#endif
	x = f;
	/*
	 * Get the upper part of the result.  Note that the divide
	 * may round up; we want to avoid this if possible, so we
	 * subtract `1/2' first.
	 */
	toppart = (x - ONE_HALF) / ONE;
	/*
	 * Now build a u_quad_t out of the top part.  The difference
	 * between x and this is the bottom part (this may introduce
	 * a few fuzzy bits, but what the heck).  With any luck this
	 * difference will be nonnegative: x should wind up in the
	 * range [0..ULONG_MAX].  For paranoia, we assume [LONG_MIN..
	 * 2*ULONG_MAX] instead.
	 */
	t.ul[H] = (unsigned long)toppart;
	t.ul[L] = 0;
	x -= (double)t.uq;
	if (x < 0) {
		t.ul[H]--;
		x += ULONG_MAX;
	}
	if (x > ULONG_MAX) {
		t.ul[H]++;
		x -= ULONG_MAX;
	}
	t.ul[L] = (u_long)x;
	return (t.uq);
}