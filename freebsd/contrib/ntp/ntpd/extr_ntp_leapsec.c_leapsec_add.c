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
struct TYPE_14__ {scalar_t__ lo; } ;
struct TYPE_17__ {TYPE_1__ D_s; } ;
typedef  TYPE_4__ vint64 ;
struct calendar {int monthday; scalar_t__ hour; int /*<<< orphan*/  month; scalar_t__ second; scalar_t__ minute; } ;
struct TYPE_16__ {scalar_t__ base_tai; scalar_t__ size; int /*<<< orphan*/  expire; } ;
struct TYPE_18__ {TYPE_3__ head; TYPE_2__* info; } ;
typedef  TYPE_5__ leap_table_t ;
struct TYPE_19__ {int dynls; scalar_t__ taiof; scalar_t__ stime; TYPE_4__ ttime; } ;
typedef  TYPE_6__ leap_info_t ;
struct TYPE_15__ {scalar_t__ taiof; int /*<<< orphan*/  ttime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int FALSE ; 
 int add_range (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_4__ ntpcal_date_to_ntp64 (struct calendar*) ; 
 int /*<<< orphan*/  ntpcal_ntp64_to_date (struct calendar*,TYPE_4__ const*) ; 
 scalar_t__ ucmpv64 (TYPE_4__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int/*BOOL*/
leapsec_add(
	leap_table_t*  pt    ,
	const vint64 * now64 ,
	int            insert)
{
	vint64		ttime, starttime;
	struct calendar	fts;
	leap_info_t	li;

	/* Check against the table expiration and the latest available
	 * leap entry. Do not permit inserts, only appends, and only if
	 * the extend the table beyond the expiration!
	 */
	if (   ucmpv64(now64, &pt->head.expire) < 0
	    || (pt->head.size && ucmpv64(now64, &pt->info[0].ttime) <= 0)) {
		errno = ERANGE;
		return FALSE;
	}

	ntpcal_ntp64_to_date(&fts, now64);
	/* To guard against dangling leap flags: do not accept leap
	 * second request on the 1st hour of the 1st day of the month.
	 */
	if (fts.monthday == 1 && fts.hour == 0) {
		errno = EINVAL;
		return FALSE;
	}

	/* Ok, do the remaining calculations */
	fts.monthday = 1;
	fts.hour     = 0;
	fts.minute   = 0;
	fts.second   = 0;
	starttime = ntpcal_date_to_ntp64(&fts);
	fts.month++;
	ttime = ntpcal_date_to_ntp64(&fts);

	li.ttime = ttime;
	li.stime = ttime.D_s.lo - starttime.D_s.lo;
	li.taiof = (pt->head.size ? pt->info[0].taiof : pt->head.base_tai)
	         + (insert ? 1 : -1);
	li.dynls = 1;
	return add_range(pt, &li);
}