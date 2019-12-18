#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ lo; } ;
struct TYPE_17__ {TYPE_3__ D_s; } ;
typedef  TYPE_4__ vint64 ;
struct calendar {int monthday; int /*<<< orphan*/  month; scalar_t__ second; scalar_t__ minute; scalar_t__ hour; } ;
struct TYPE_14__ {scalar_t__ size; } ;
struct TYPE_18__ {TYPE_2__* info; TYPE_1__ head; } ;
typedef  TYPE_5__ leap_table_t ;
struct TYPE_19__ {int dynls; scalar_t__ taiof; scalar_t__ stime; TYPE_4__ ttime; } ;
typedef  TYPE_6__ leap_info_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_15__ {int taiof; int /*<<< orphan*/  ttime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int FALSE ; 
 int TRUE ; 
 int add_range (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_4__ ntpcal_date_to_ntp64 (struct calendar*) ; 
 int /*<<< orphan*/  ntpcal_ntp64_to_date (struct calendar*,TYPE_4__ const*) ; 
 int ucmpv64 (TYPE_4__ const*,int /*<<< orphan*/ *) ; 

int/*BOOL*/
leapsec_raw(
	leap_table_t * pt,
	const vint64 * ttime,
	int            taiof,
	int            dynls)
{
	vint64		starttime;
	struct calendar	fts;
	leap_info_t	li;

	/* Check that we either extend the table or get a duplicate of
	 * the latest entry. The latter is a benevolent overwrite with
	 * identical data and could happen if we get an autokey message
	 * that extends the lifetime of the current leapsecond table.
	 * Otherwise paranoia rulez!
	 */
	if (pt->head.size) {
		int cmp = ucmpv64(ttime, &pt->info[0].ttime);
		if (cmp == 0)
			cmp -= (taiof != pt->info[0].taiof);
		if (cmp < 0) {
			errno = ERANGE;
			return FALSE;
		}
		if (cmp == 0)
			return TRUE;
	}

	ntpcal_ntp64_to_date(&fts, ttime);
	/* If this does not match the exact month start, bail out. */
	if (fts.monthday != 1 || fts.hour || fts.minute || fts.second) {
		errno = EINVAL;
		return FALSE;
	}
	fts.month--; /* was in range 1..12, no overflow here! */
	starttime = ntpcal_date_to_ntp64(&fts);
	li.ttime = *ttime;
	li.stime = ttime->D_s.lo - starttime.D_s.lo;
	li.taiof = (int16_t)taiof;
	li.dynls = (dynls != 0);
	return add_range(pt, &li);
}