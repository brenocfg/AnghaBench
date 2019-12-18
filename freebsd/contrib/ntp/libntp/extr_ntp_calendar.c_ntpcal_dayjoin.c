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
struct TYPE_4__ {int lo; int hi; } ;
struct TYPE_5__ {int q_s; TYPE_1__ D_s; } ;
typedef  TYPE_2__ vint64 ;
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ADD (int,int,int,int) ; 
 int /*<<< orphan*/  M_NEG (int,int) ; 
 int SECSPERDAY ; 

vint64
ntpcal_dayjoin(
	int32_t days,
	int32_t secs
	)
{
	vint64 res;

#   if defined(HAVE_INT64)

	res.q_s	 = days;
	res.q_s *= SECSPERDAY;
	res.q_s += secs;

#   else

	uint32_t p1, p2;
	int	 isneg;

	/*
	 * res = days *86400 + secs, using manual 16/32 bit
	 * multiplications and shifts.
	 */
	isneg = (days < 0);
	if (isneg)
		days = -days;

	/* assemble days * 675 */
	res.D_s.lo = (days & 0xFFFF) * 675u;
	res.D_s.hi = 0;
	p1 = (days >> 16) * 675u;
	p2 = p1 >> 16;
	p1 = p1 << 16;
	M_ADD(res.D_s.hi, res.D_s.lo, p2, p1);

	/* mul by 128, using shift */
	res.D_s.hi = (res.D_s.hi << 7) | (res.D_s.lo >> 25);
	res.D_s.lo = (res.D_s.lo << 7);

	/* fix sign */
	if (isneg)
		M_NEG(res.D_s.hi, res.D_s.lo);

	/* properly add seconds */
	p2 = 0;
	if (secs < 0) {
		p1 = (uint32_t)-secs;
		M_NEG(p2, p1);
	} else {
		p1 = (uint32_t)secs;
	}
	M_ADD(res.D_s.hi, res.D_s.lo, p2, p1);

#   endif

	return res;
}