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
typedef  int uint64_t ;

/* Variables and functions */
 int flsll (int) ; 

__attribute__((used)) static uint64_t
mul64_by_fraction(uint64_t a, uint64_t b, uint64_t c)
{
	uint64_t acc, bh, bl;
	int i, s, sa, sb;

	/*
	 * Calculate (a * b) / c accurately enough without overflowing.  c
	 * must be nonzero, and its top bit must be 0.  a or b must be
	 * <= c, and the implementation is tuned for b <= c.
	 *
	 * The comments about times are for use in calcru1() with units of
	 * microseconds for 'a' and stathz ticks at 128 Hz for b and c.
	 *
	 * Let n be the number of top zero bits in c.  Each iteration
	 * either returns, or reduces b by right shifting it by at least n.
	 * The number of iterations is at most 1 + 64 / n, and the error is
	 * at most the number of iterations.
	 *
	 * It is very unusual to need even 2 iterations.  Previous
	 * implementations overflowed essentially by returning early in the
	 * first iteration, with n = 38 giving overflow at 105+ hours and
	 * n = 32 giving overlow at at 388+ days despite a more careful
	 * calculation.  388 days is a reasonable uptime, and the calculation
	 * needs to work for the uptime times the number of CPUs since 'a'
	 * is per-process.
	 */
	if (a >= (uint64_t)1 << 63)
		return (0);		/* Unsupported arg -- can't happen. */
	acc = 0;
	for (i = 0; i < 128; i++) {
		sa = flsll(a);
		sb = flsll(b);
		if (sa + sb <= 64)
			/* Up to 105 hours on first iteration. */
			return (acc + (a * b) / c);
		if (a >= c) {
			/*
			 * This reduction is based on a = q * c + r, with the
			 * remainder r < c.  'a' may be large to start, and
			 * moving bits from b into 'a' at the end of the loop
			 * sets the top bit of 'a', so the reduction makes
			 * significant progress.
			 */
			acc += (a / c) * b;
			a %= c;
			sa = flsll(a);
			if (sa + sb <= 64)
				/* Up to 388 days on first iteration. */
				return (acc + (a * b) / c);
		}

		/*
		 * This step writes a * b as a * ((bh << s) + bl) =
		 * a * (bh << s) + a * bl = (a << s) * bh + a * bl.  The 2
		 * additive terms are handled separately.  Splitting in
		 * this way is linear except for rounding errors.
		 *
		 * s = 64 - sa is the maximum such that a << s fits in 64
		 * bits.  Since a < c and c has at least 1 zero top bit,
		 * sa < 64 and s > 0.  Thus this step makes progress by
		 * reducing b (it increases 'a', but taking remainders on
		 * the next iteration completes the reduction).
		 *
		 * Finally, the choice for s is just what is needed to keep
		 * a * bl from overflowing, so we don't need complications
		 * like a recursive call mul64_by_fraction(a, bl, c) to
		 * handle the second additive term.
		 */
		s = 64 - sa;
		bh = b >> s;
		bl = b - (bh << s);
		acc += (a * bl) / c;
		a <<= s;
		b = bh;
	}
	return (0);		/* Algorithm failure -- can't happen. */
}