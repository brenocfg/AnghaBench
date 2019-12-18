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
 int powmod (int,int,int) ; 

__attribute__((used)) static int
spsp(uint64_t n, uint64_t p)
{
	uint64_t x;
	uint64_t r = n - 1;
	int k = 0;

	/* Compute n - 1 = 2^k * r. */
	while ((r & 1) == 0) {
		k++;
		r >>= 1;
	}

	/* Compute x = p^r mod n.  If x = 1, n is a p-spsp. */
	x = powmod(p, r, n);
	if (x == 1)
		return (1);

	/* Compute x^(2^i) for 0 <= i < n.  If any are -1, n is a p-spsp. */
	while (k > 0) {
		if (x == n - 1)
			return (1);
		x = powmod(x, 2, n);
		k--;
	}

	/* Not a p-spsp. */
	return (0);
}