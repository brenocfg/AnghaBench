#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {long* cp_time; long double snap_time; TYPE_1__* dinfo; } ;
struct TYPE_9__ {scalar_t__ selected; int position; int /*<<< orphan*/  unit_number; int /*<<< orphan*/ * device_name; } ;
struct TYPE_8__ {long* cp_time; long double snap_time; TYPE_2__* dinfo; } ;
struct TYPE_7__ {int /*<<< orphan*/ * devices; } ;
struct TYPE_6__ {int /*<<< orphan*/ * devices; } ;

/* Variables and functions */
 int CPUSTATES ; 
 int /*<<< orphan*/  DSM_NONE ; 
 int /*<<< orphan*/  DSM_TRANSFERS_PER_SECOND ; 
 TYPE_5__ cur ; 
 TYPE_4__* dev_select ; 
 scalar_t__ devstat_compute_statistics (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long double,int /*<<< orphan*/ ,long double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devstat_errbuf ; 
 TYPE_3__ last ; 
 scalar_t__ maxshowdevs ; 
 int num_devices ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long double) ; 
 int /*<<< orphan*/  xo_errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
devstats(void)
{
	long double busy_seconds, transfers_per_second;
	long tmp;
	int di, dn, state;

	for (state = 0; state < CPUSTATES; ++state) {
		tmp = cur.cp_time[state];
		cur.cp_time[state] -= last.cp_time[state];
		last.cp_time[state] = tmp;
	}

	busy_seconds = cur.snap_time - last.snap_time;

	xo_open_list("device");
	for (dn = 0; dn < num_devices; dn++) {
		if (dev_select[dn].selected == 0 ||
		    dev_select[dn].selected > maxshowdevs)
			continue;

		di = dev_select[dn].position;

		if (devstat_compute_statistics(&cur.dinfo->devices[di],
		    &last.dinfo->devices[di], busy_seconds,
		    DSM_TRANSFERS_PER_SECOND, &transfers_per_second,
		    DSM_NONE) != 0)
			xo_errx(1, "%s", devstat_errbuf);

		xo_open_instance("device");
		xo_emit("{ekq:name/%c%c%d}{:transfers/%3.0Lf} ",
		    dev_select[dn].device_name[0],
		    dev_select[dn].device_name[1],
		    dev_select[dn].unit_number,
		    transfers_per_second);
		xo_close_instance("device");
	}
	xo_close_list("device");
}