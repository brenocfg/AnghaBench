#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int exp; int manl; } ;
union IEEEl2bits {TYPE_1__ bits; int /*<<< orphan*/  e; } ;
struct dd {int lo; int /*<<< orphan*/  hi; } ;

/* Variables and functions */
 int INFINITY ; 
 struct dd dd_add (long double,long double) ; 
 long double ldexp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nextafterl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline long double
add_and_denormalize(long double a, long double b, int scale)
{
	struct dd sum;
	int bits_lost;
	union IEEEl2bits u;

	sum = dd_add(a, b);

	/*
	 * If we are losing at least two bits of accuracy to denormalization,
	 * then the first lost bit becomes a round bit, and we adjust the
	 * lowest bit of sum.hi to make it a sticky bit summarizing all the
	 * bits in sum.lo. With the sticky bit adjusted, the hardware will
	 * break any ties in the correct direction.
	 *
	 * If we are losing only one bit to denormalization, however, we must
	 * break the ties manually.
	 */
	if (sum.lo != 0) {
		u.e = sum.hi;
		bits_lost = -u.bits.exp - scale + 1;
		if ((bits_lost != 1) ^ (int)(u.bits.manl & 1))
			sum.hi = nextafterl(sum.hi, INFINITY * sum.lo);
	}
	return (ldexp(sum.hi, scale));
}