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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long ubig ;

/* Variables and functions */
 int /*<<< orphan*/  spsp (unsigned long long,int) ; 

int
isprime(ubig _n)
{
	uint64_t n = _n;

	/*
	 * Values from:
	 * C. Pomerance, J.L. Selfridge, and S.S. Wagstaff, Jr.,
	 * The pseudoprimes to 25 * 10^9, Math. Comp. 35(151):1003-1026, 1980.
	 */

	/* No SPSPs to base 2 less than 2047. */
	if (!spsp(n, 2))
		return (0);
	if (n < 2047ULL)
		return (1);

	/* No SPSPs to bases 2,3 less than 1373653. */
	if (!spsp(n, 3))
		return (0);
	if (n < 1373653ULL)
		return (1);

	/* No SPSPs to bases 2,3,5 less than 25326001. */
	if (!spsp(n, 5))
		return (0);
	if (n < 25326001ULL)
		return (1);

	/* No SPSPs to bases 2,3,5,7 less than 3215031751. */
	if (!spsp(n, 7))
		return (0);
	if (n < 3215031751ULL)
		return (1);

	/*
	 * Values from:
	 * G. Jaeschke, On strong pseudoprimes to several bases,
	 * Math. Comp. 61(204):915-926, 1993.
	 */

	/* No SPSPs to bases 2,3,5,7,11 less than 2152302898747. */
	if (!spsp(n, 11))
		return (0);
	if (n < 2152302898747ULL)
		return (1);

	/* No SPSPs to bases 2,3,5,7,11,13 less than 3474749660383. */
	if (!spsp(n, 13))
		return (0);
	if (n < 3474749660383ULL)
		return (1);

	/* No SPSPs to bases 2,3,5,7,11,13,17 less than 341550071728321. */
	if (!spsp(n, 17))
		return (0);
	if (n < 341550071728321ULL)
		return (1);

	/* No SPSPs to bases 2,3,5,7,11,13,17,19 less than 341550071728321. */
	if (!spsp(n, 19))
		return (0);
	if (n < 341550071728321ULL)
		return (1);

	/*
	 * Value from:
	 * Y. Jiang and Y. Deng, Strong pseudoprimes to the first eight prime
	 * bases, Math. Comp. 83(290):2915-2924, 2014.
	 */

	/* No SPSPs to bases 2..23 less than 3825123056546413051. */
	if (!spsp(n, 23))
		return (0);
	if (n < 3825123056546413051)
		return (1);

	/*
	 * Value from:
	 * J. Sorenson and J. Webster, Strong pseudoprimes to twelve prime
	 * bases, Math. Comp. 86(304):985-1003, 2017.
	 */

	/* No SPSPs to bases 2..37 less than 318665857834031151167461. */
	if (!spsp(n, 29))
		return (0);
	if (!spsp(n, 31))
		return (0);
	if (!spsp(n, 37))
		return (0);

	/* All 64-bit values are less than 318665857834031151167461. */
	return (1);
}