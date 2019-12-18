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
typedef  unsigned int u64 ;
struct throtl_grp {unsigned long* slice_start; unsigned int* bytes_disp; TYPE_1__* td; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {unsigned long throtl_slice; } ;

/* Variables and functions */
 unsigned int HZ ; 
 int bio_data_dir (struct bio*) ; 
 unsigned long div64_u64 (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  do_div (unsigned int,unsigned int) ; 
 unsigned long jiffies ; 
 unsigned long roundup (unsigned long,unsigned long) ; 
 unsigned long tg_bps_limit (struct throtl_grp*,int) ; 
 unsigned int throtl_bio_data_size (struct bio*) ; 

__attribute__((used)) static bool tg_with_in_bps_limit(struct throtl_grp *tg, struct bio *bio,
				 unsigned long *wait)
{
	bool rw = bio_data_dir(bio);
	u64 bytes_allowed, extra_bytes, tmp;
	unsigned long jiffy_elapsed, jiffy_wait, jiffy_elapsed_rnd;
	unsigned int bio_size = throtl_bio_data_size(bio);

	jiffy_elapsed = jiffy_elapsed_rnd = jiffies - tg->slice_start[rw];

	/* Slice has just started. Consider one slice interval */
	if (!jiffy_elapsed)
		jiffy_elapsed_rnd = tg->td->throtl_slice;

	jiffy_elapsed_rnd = roundup(jiffy_elapsed_rnd, tg->td->throtl_slice);

	tmp = tg_bps_limit(tg, rw) * jiffy_elapsed_rnd;
	do_div(tmp, HZ);
	bytes_allowed = tmp;

	if (tg->bytes_disp[rw] + bio_size <= bytes_allowed) {
		if (wait)
			*wait = 0;
		return true;
	}

	/* Calc approx time to dispatch */
	extra_bytes = tg->bytes_disp[rw] + bio_size - bytes_allowed;
	jiffy_wait = div64_u64(extra_bytes * HZ, tg_bps_limit(tg, rw));

	if (!jiffy_wait)
		jiffy_wait = 1;

	/*
	 * This wait time is without taking into consideration the rounding
	 * up we did. Add that time also.
	 */
	jiffy_wait = jiffy_wait + (jiffy_elapsed_rnd - jiffy_elapsed);
	if (wait)
		*wait = jiffy_wait;
	return false;
}