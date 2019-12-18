#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lo; } ;
struct TYPE_6__ {scalar_t__ hi; } ;
struct TYPE_8__ {scalar_t__ q_s; TYPE_2__ D_s; TYPE_1__ d_s; } ;
typedef  TYPE_3__ vint64 ;

/* Variables and functions */

int
icmpv64(
	const vint64 * lhs,
	const vint64 * rhs
	)
{
	int res;

#if defined(HAVE_INT64)
	res = (lhs->q_s > rhs->q_s)
	    - (lhs->q_s < rhs->q_s);
#else	
	res = (lhs->d_s.hi > rhs->d_s.hi)
	    - (lhs->d_s.hi < rhs->d_s.hi);
	if ( ! res )
		res = (lhs->D_s.lo > rhs->D_s.lo)
		    - (lhs->D_s.lo < rhs->D_s.lo);
#endif

	return res;
}