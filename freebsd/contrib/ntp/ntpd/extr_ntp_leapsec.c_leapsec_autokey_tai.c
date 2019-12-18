#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vint64 ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_8__ {scalar_t__ base_tai; int size; int this_tai; int next_tai; } ;
struct TYPE_10__ {TYPE_2__* info; TYPE_1__ head; } ;
typedef  TYPE_3__ leap_table_t ;
struct TYPE_11__ {scalar_t__ taiof; void* ttime; void* ebase; } ;
typedef  TYPE_4__ leap_era_t ;
struct TYPE_9__ {int taiof; int /*<<< orphan*/  dynls; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 void* addv64i32 (void**,int) ; 
 int /*<<< orphan*/  fetch_leap_era (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* leapsec_get_table (int) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ ucmpv64 (int /*<<< orphan*/ *,void**) ; 

int/*BOOL*/
leapsec_autokey_tai(
	int            tai_offset,
	uint32_t       ntpnow    ,
	const time_t * pivot     )
{
	leap_table_t * pt;
	leap_era_t     era;
	vint64         now64;
	int            idx;

	(void)tai_offset;
	pt = leapsec_get_table(FALSE);

	/* Bail out if the basic offset is not zero and the putative
	 * offset is bigger than 10s. That was in 1972 -- we don't want
	 * to go back that far!
	 */
	if (pt->head.base_tai != 0 || tai_offset < 10)
		return FALSE;

	/* If there's already data in the table, check if an update is
	 * possible. Update is impossible if there are static entries
	 * (since this indicates a valid leapsecond file) or if we're
	 * too close to a leapsecond transition: We do not know on what
	 * side the transition the sender might have been, so we use a
	 * dead zone around the transition.
	 */

	/* Check for static entries */
	for (idx = 0; idx != pt->head.size; idx++)
		if ( ! pt->info[idx].dynls)
			return FALSE;

	/* get the fulll time stamp and leap era for it */
	now64 = ntpcal_ntp_to_ntp(ntpnow, pivot);
	fetch_leap_era(&era, pt, &now64);

	/* check the limits with 20s dead band */
	era.ebase = addv64i32(&era.ebase,  20);
	if (ucmpv64(&now64, &era.ebase) < 0)
		return FALSE;

	era.ttime = addv64i32(&era.ttime, -20);
	if (ucmpv64(&now64, &era.ttime) > 0)
		return FALSE;

	/* Here we can proceed. Calculate the delta update. */
	tai_offset -= era.taiof;

	/* Shift the header info offsets. */
	pt->head.base_tai += tai_offset;
	pt->head.this_tai += tai_offset;
	pt->head.next_tai += tai_offset;

	/* Shift table entry offsets (if any) */
	for (idx = 0; idx != pt->head.size; idx++)
		pt->info[idx].taiof += tai_offset;

	/* claim success... */
	return TRUE;
}