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
typedef  int u64 ;
struct TYPE_8__ {int shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; } ;
struct vvar_data {int wall_time_snsec; int monotonic_time_snsec; long wall_time_coarse_nsec; scalar_t__ monotonic_time_coarse_nsec; scalar_t__ monotonic_time_coarse_sec; scalar_t__ wall_time_coarse_sec; scalar_t__ monotonic_time_sec; scalar_t__ wall_time_sec; TYPE_3__ clock; int /*<<< orphan*/  vclock_mode; } ;
struct TYPE_10__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_9__ {int shift; int xtime_nsec; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; TYPE_2__* clock; } ;
struct timekeeper {TYPE_5__ wall_to_monotonic; TYPE_4__ tkr_mono; scalar_t__ xtime_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  vclock_mode; } ;
struct TYPE_7__ {TYPE_1__ archdata; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct vvar_data* vvar_data ; 
 int /*<<< orphan*/  vvar_write_begin (struct vvar_data*) ; 
 int /*<<< orphan*/  vvar_write_end (struct vvar_data*) ; 

void update_vsyscall(struct timekeeper *tk)
{
	struct vvar_data *vdata = vvar_data;

	if (unlikely(vdata == NULL))
		return;

	vvar_write_begin(vdata);
	vdata->vclock_mode = tk->tkr_mono.clock->archdata.vclock_mode;
	vdata->clock.cycle_last = tk->tkr_mono.cycle_last;
	vdata->clock.mask = tk->tkr_mono.mask;
	vdata->clock.mult = tk->tkr_mono.mult;
	vdata->clock.shift = tk->tkr_mono.shift;

	vdata->wall_time_sec = tk->xtime_sec;
	vdata->wall_time_snsec = tk->tkr_mono.xtime_nsec;

	vdata->monotonic_time_sec = tk->xtime_sec +
				    tk->wall_to_monotonic.tv_sec;
	vdata->monotonic_time_snsec = tk->tkr_mono.xtime_nsec +
				      (tk->wall_to_monotonic.tv_nsec <<
				       tk->tkr_mono.shift);

	while (vdata->monotonic_time_snsec >=
	       (((u64)NSEC_PER_SEC) << tk->tkr_mono.shift)) {
		vdata->monotonic_time_snsec -=
				((u64)NSEC_PER_SEC) << tk->tkr_mono.shift;
		vdata->monotonic_time_sec++;
	}

	vdata->wall_time_coarse_sec = tk->xtime_sec;
	vdata->wall_time_coarse_nsec =
			(long)(tk->tkr_mono.xtime_nsec >> tk->tkr_mono.shift);

	vdata->monotonic_time_coarse_sec =
		vdata->wall_time_coarse_sec + tk->wall_to_monotonic.tv_sec;
	vdata->monotonic_time_coarse_nsec =
		vdata->wall_time_coarse_nsec + tk->wall_to_monotonic.tv_nsec;

	while (vdata->monotonic_time_coarse_nsec >= NSEC_PER_SEC) {
		vdata->monotonic_time_coarse_nsec -= NSEC_PER_SEC;
		vdata->monotonic_time_coarse_sec++;
	}

	vvar_write_end(vdata);
}