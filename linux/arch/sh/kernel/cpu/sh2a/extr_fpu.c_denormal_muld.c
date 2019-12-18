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

/* Variables and functions */
 int /*<<< orphan*/  mult64 (unsigned long long,unsigned long long,unsigned long long*,unsigned long long*) ; 
 int rshift64 (unsigned long long,unsigned long long,int) ; 

__attribute__((used)) static long long denormal_muld(long long hx, long long hy)
{
	unsigned long long ix, iy;
	unsigned long long mh, ml, nh, nl;
	int exp, w;

	ix = hx & 0x7fffffffffffffffLL;
	iy = hy & 0x7fffffffffffffffLL;
	if (iy < 0x0010000000000000LL || ix == 0)
		return ((hx ^ hy) & 0x8000000000000000LL);

	exp = (iy & 0x7ff0000000000000LL) >> 52;
	ix &= 0x000fffffffffffffLL;
	iy = (iy & 0x000fffffffffffffLL) | 0x0010000000000000LL;
	mult64(ix, iy, &mh, &ml);
	nh = mh;
	nl = ml;
	w = -1;
	if (nh) {
		while (nh) { nh >>= 1; w++;}
		w += 64;
	} else
		while (nl) { nl >>= 1; w++;}

	/* FIXME: use guard bits */
	exp += w - 1022 - 52 * 2;
	if (exp > 0)
		ix = (rshift64(mh, ml, w - 52) & 0x000fffffffffffffLL)
			| ((long long)exp << 52);
	else if (exp + 51 >= 0)
		ix = rshift64(mh, ml, w - 51 - exp) & 0x000fffffffffffffLL;
	else
		ix = 0;

	ix |= (hx ^ hy) & 0x8000000000000000LL;
	return ix;
}