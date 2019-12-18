#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_7__ {TYPE_1__ D_s; scalar_t__ Q_s; } ;
typedef  TYPE_2__ vint64 ;

/* Variables and functions */
 int /*<<< orphan*/  M_SUB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vint64
subv64(
	const vint64 *lhs,
	const vint64 *rhs
	)
{
	vint64 res;

#if defined(HAVE_INT64)
	res.Q_s = lhs->Q_s - rhs->Q_s;
#else
	res = *lhs;
	M_SUB(res.D_s.hi, res.D_s.lo, rhs->D_s.hi, rhs->D_s.lo);
#endif
	return res;
}