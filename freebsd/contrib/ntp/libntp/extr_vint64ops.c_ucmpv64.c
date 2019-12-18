#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hi; scalar_t__ lo; } ;
struct TYPE_6__ {scalar_t__ Q_s; TYPE_1__ D_s; } ;
typedef  TYPE_2__ vint64 ;

/* Variables and functions */

int
ucmpv64(
	const vint64 * lhs,
	const vint64 * rhs
	)
{
	int res;
	
#if defined(HAVE_INT64)
	res = (lhs->Q_s > rhs->Q_s)
	    - (lhs->Q_s < rhs->Q_s);
#else	
	res = (lhs->D_s.hi > rhs->D_s.hi)
	    - (lhs->D_s.hi < rhs->D_s.hi);
	if ( ! res )
		res = (lhs->D_s.lo > rhs->D_s.lo)
		    - (lhs->D_s.lo < rhs->D_s.lo);
#endif
	return res;
}