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
struct ld {long double hi; long double lo; int /*<<< orphan*/  lo_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOPRINT_START (long double*) ; 
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  RETURN2PI (long double,long double) ; 
 int /*<<< orphan*/  RETURNPI (long double) ; 
 int /*<<< orphan*/  _2sumF (long double,long double) ; 
 long double invln10_hi ; 
 long double invln10_lo ; 
 int /*<<< orphan*/  k_logl (long double,struct ld*) ; 

long double
log10l(long double x)
{
	struct ld r;
	long double hi, lo;

	ENTERI();
	DOPRINT_START(&x);
	k_logl(x, &r);
	if (!r.lo_set)
		RETURNPI(r.hi);
	_2sumF(r.hi, r.lo);
	hi = (float)r.hi;
	lo = r.lo + (r.hi - hi);
	RETURN2PI(invln10_hi * hi,
	    (invln10_lo + invln10_hi) * lo + invln10_lo * hi);
}