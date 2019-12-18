#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct throtl_grp {unsigned long* slice_start; int* io_disp; TYPE_1__* td; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  throtl_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 unsigned long UINT_MAX ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long roundup (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ tg_iops_limit (struct throtl_grp*,int) ; 

__attribute__((used)) static bool tg_with_in_iops_limit(struct throtl_grp *tg, struct bio *bio,
				  unsigned long *wait)
{
	bool rw = bio_data_dir(bio);
	unsigned int io_allowed;
	unsigned long jiffy_elapsed, jiffy_wait, jiffy_elapsed_rnd;
	u64 tmp;

	jiffy_elapsed = jiffies - tg->slice_start[rw];

	/* Round up to the next throttle slice, wait time must be nonzero */
	jiffy_elapsed_rnd = roundup(jiffy_elapsed + 1, tg->td->throtl_slice);

	/*
	 * jiffy_elapsed_rnd should not be a big value as minimum iops can be
	 * 1 then at max jiffy elapsed should be equivalent of 1 second as we
	 * will allow dispatch after 1 second and after that slice should
	 * have been trimmed.
	 */

	tmp = (u64)tg_iops_limit(tg, rw) * jiffy_elapsed_rnd;
	do_div(tmp, HZ);

	if (tmp > UINT_MAX)
		io_allowed = UINT_MAX;
	else
		io_allowed = tmp;

	if (tg->io_disp[rw] + 1 <= io_allowed) {
		if (wait)
			*wait = 0;
		return true;
	}

	/* Calc approx time to dispatch */
	jiffy_wait = jiffy_elapsed_rnd - jiffy_elapsed;

	if (wait)
		*wait = jiffy_wait;
	return false;
}