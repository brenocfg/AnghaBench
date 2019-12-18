#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lo; } ;
struct TYPE_5__ {scalar_t__ hi; } ;
struct TYPE_7__ {TYPE_2__ D_s; TYPE_1__ d_s; scalar_t__ q_s; } ;
typedef  TYPE_3__ vint64 ;
typedef  int time_t ;

/* Variables and functions */

time_t
vint64_to_time(
	const vint64 *tv
	)
{
	time_t res;

#   if SIZEOF_TIME_T <= 4

	res = (time_t)tv->D_s.lo;

#   elif defined(HAVE_INT64)

	res = (time_t)tv->q_s;

#   else

	res = ((time_t)tv->d_s.hi << 32) | tv->D_s.lo;

#   endif

	return res;
}