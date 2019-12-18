#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* hi; void* lo; } ;
struct TYPE_5__ {int q_s; TYPE_1__ D_s; } ;
typedef  TYPE_2__ vint64 ;
typedef  void* uint32_t ;
typedef  int time_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NEG (void*,void*) ; 

vint64
time_to_vint64(
	const time_t * ptt
	)
{
	vint64 res;
	time_t tt;

	tt = *ptt;

#   if SIZEOF_TIME_T <= 4

	res.D_s.hi = 0;
	if (tt < 0) {
		res.D_s.lo = (uint32_t)-tt;
		M_NEG(res.D_s.hi, res.D_s.lo);
	} else {
		res.D_s.lo = (uint32_t)tt;
	}

#   elif defined(HAVE_INT64)

	res.q_s = tt;

#   else
	/*
	 * shifting negative signed quantities is compiler-dependent, so
	 * we better avoid it and do it all manually. And shifting more
	 * than the width of a quantity is undefined. Also a don't do!
	 */
	if (tt < 0) {
		tt = -tt;
		res.D_s.lo = (uint32_t)tt;
		res.D_s.hi = (uint32_t)(tt >> 32);
		M_NEG(res.D_s.hi, res.D_s.lo);
	} else {
		res.D_s.lo = (uint32_t)tt;
		res.D_s.hi = (uint32_t)(tt >> 32);
	}

#   endif

	return res;
}