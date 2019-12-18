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
 int abs (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int mask (int) ; 
 int random () ; 
 double remainder (double,double) ; 
 double remquo (double,double,int*) ; 
 int /*<<< orphan*/  signbit (double) ; 

__attribute__((used)) static void
testd(double x, double y, double expected_rem, int expected_quo)
{
	int q;
	double rem;

	q = random();
	rem = remainder(x, y);
	assert(rem == expected_rem);
	assert(!signbit(rem) == !signbit(expected_rem));
	rem = remquo(x, y, &q);
	assert(rem == expected_rem);
	assert(!signbit(rem) == !signbit(expected_rem));
	assert((q ^ expected_quo) >= 0); /* sign(q) == sign(expected_quo) */
	assert((q & 0x7) == (expected_quo & 0x7));
	if (q != 0) {
		assert((q > 0) ^ !(expected_quo > 0));
		q = abs(q);
		assert(q == (abs(expected_quo) & mask(q)));
	}
}