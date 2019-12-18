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
struct dd {scalar_t__ lo; scalar_t__ hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_WORD64 (int,scalar_t__) ; 
 int /*<<< orphan*/  INSERT_WORD64 (scalar_t__,int) ; 
 struct dd dd_add (double,double) ; 
 double ldexp (scalar_t__,int) ; 

__attribute__((used)) static inline double
add_and_denormalize(double a, double b, int scale)
{
	struct dd sum;
	uint64_t hibits, lobits;
	int bits_lost;

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
		EXTRACT_WORD64(hibits, sum.hi);
		bits_lost = -((int)(hibits >> 52) & 0x7ff) - scale + 1;
		if ((bits_lost != 1) ^ (int)(hibits & 1)) {
			/* hibits += (int)copysign(1.0, sum.hi * sum.lo) */
			EXTRACT_WORD64(lobits, sum.lo);
			hibits += 1 - (((hibits ^ lobits) >> 62) & 2);
			INSERT_WORD64(sum.hi, hibits);
		}
	}
	return (ldexp(sum.hi, scale));
}