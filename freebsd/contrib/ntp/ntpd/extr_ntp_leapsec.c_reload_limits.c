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
typedef  int /*<<< orphan*/  vint64 ;
struct TYPE_6__ {int size; int /*<<< orphan*/  dynls; scalar_t__ this_tai; scalar_t__ next_tai; int /*<<< orphan*/  ttime; int /*<<< orphan*/  dtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  ebase; scalar_t__ base_tai; } ;
struct TYPE_7__ {TYPE_2__ head; TYPE_1__* info; } ;
typedef  TYPE_3__ leap_table_t ;
struct TYPE_5__ {int /*<<< orphan*/  stime; int /*<<< orphan*/  ttime; int /*<<< orphan*/  dynls; scalar_t__ taiof; } ;

/* Variables and functions */
 scalar_t__ _electric ; 
 int /*<<< orphan*/  addv64i32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  subv64u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ucmpv64 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reload_limits(
	leap_table_t * pt,
	const vint64 * ts)
{
	int idx;

	/* Get full time and search the true lower bound. Use a
	 * simple loop here, since the number of entries does
	 * not warrant a binary search. This also works for an empty
	 * table, so there is no shortcut for that case.
	 */
	for (idx = 0; idx != pt->head.size; idx++)
		if (ucmpv64(ts, &pt->info[idx].ttime) >= 0)
			break;

	/* get time limits with proper bound conditions. Note that the
	 * bounds of the table will be observed even if the table is
	 * empty -- no undefined condition must arise from this code.
	 */
	if (idx >= pt->head.size) {
		memset(&pt->head.ebase, 0x00, sizeof(vint64));
		pt->head.this_tai = pt->head.base_tai;
	} else {
		pt->head.ebase    = pt->info[idx].ttime;
		pt->head.this_tai = pt->info[idx].taiof;
	}
	if (--idx >= 0) {
		pt->head.next_tai = pt->info[idx].taiof;
		pt->head.dynls    = pt->info[idx].dynls;
		pt->head.ttime    = pt->info[idx].ttime;

		if (_electric)
			pt->head.dtime = pt->head.ttime;
                else
			pt->head.dtime = addv64i32(
				&pt->head.ttime,
				pt->head.next_tai - pt->head.this_tai);

		pt->head.stime = subv64u32(
			&pt->head.ttime, pt->info[idx].stime);

	} else {
		memset(&pt->head.ttime, 0xFF, sizeof(vint64));
		pt->head.stime    = pt->head.ttime;
		pt->head.dtime    = pt->head.ttime;
		pt->head.next_tai = pt->head.this_tai;
		pt->head.dynls    = 0;
	}
}