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
struct TYPE_5__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_6__ {TYPE_1__ D_s; int /*<<< orphan*/  Q_s; } ;
typedef  TYPE_2__ vint64 ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vint64
addv64u32(
	const vint64 * lhs,
	uint32_t       rhs
	)
{
	vint64 res;

	res = *lhs;
#if defined(HAVE_INT64)
	res.Q_s += rhs;
#else
	M_ADD(res.D_s.hi, res.D_s.lo, 0, rhs);
#endif
	return res;
}