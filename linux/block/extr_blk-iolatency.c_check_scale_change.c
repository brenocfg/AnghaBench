#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_7__ {int /*<<< orphan*/  wait; } ;
struct TYPE_6__ {int max_depth; } ;
struct child_latency_info {int nr_samples; int /*<<< orphan*/  scale_lat; int /*<<< orphan*/  scale_cookie; } ;
struct iolatency_grp {scalar_t__ min_lat_nsec; scalar_t__ nr_samples; TYPE_2__ rq_wait; TYPE_1__ rq_depth; int /*<<< orphan*/  scale_cookie; struct child_latency_info child_lat; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 unsigned int DEFAULT_SCALE_COOKIE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int UINT_MAX ; 
 unsigned int atomic_cmpxchg (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkcg_clear_delay (TYPE_3__*) ; 
 int /*<<< orphan*/  blkcg_use_delay (TYPE_3__*) ; 
 struct iolatency_grp* blkg_to_lat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  div64_u64 (scalar_t__,int) ; 
 TYPE_3__* lat_to_blkg (struct iolatency_grp*) ; 
 scalar_t__ max (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_change (struct iolatency_grp*,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_scale_change(struct iolatency_grp *iolat)
{
	struct iolatency_grp *parent;
	struct child_latency_info *lat_info;
	unsigned int cur_cookie;
	unsigned int our_cookie = atomic_read(&iolat->scale_cookie);
	u64 scale_lat;
	unsigned int old;
	int direction = 0;

	if (lat_to_blkg(iolat)->parent == NULL)
		return;

	parent = blkg_to_lat(lat_to_blkg(iolat)->parent);
	if (!parent)
		return;

	lat_info = &parent->child_lat;
	cur_cookie = atomic_read(&lat_info->scale_cookie);
	scale_lat = READ_ONCE(lat_info->scale_lat);

	if (cur_cookie < our_cookie)
		direction = -1;
	else if (cur_cookie > our_cookie)
		direction = 1;
	else
		return;

	old = atomic_cmpxchg(&iolat->scale_cookie, our_cookie, cur_cookie);

	/* Somebody beat us to the punch, just bail. */
	if (old != our_cookie)
		return;

	if (direction < 0 && iolat->min_lat_nsec) {
		u64 samples_thresh;

		if (!scale_lat || iolat->min_lat_nsec <= scale_lat)
			return;

		/*
		 * Sometimes high priority groups are their own worst enemy, so
		 * instead of taking it out on some poor other group that did 5%
		 * or less of the IO's for the last summation just skip this
		 * scale down event.
		 */
		samples_thresh = lat_info->nr_samples * 5;
		samples_thresh = max(1ULL, div64_u64(samples_thresh, 100));
		if (iolat->nr_samples <= samples_thresh)
			return;
	}

	/* We're as low as we can go. */
	if (iolat->rq_depth.max_depth == 1 && direction < 0) {
		blkcg_use_delay(lat_to_blkg(iolat));
		return;
	}

	/* We're back to the default cookie, unthrottle all the things. */
	if (cur_cookie == DEFAULT_SCALE_COOKIE) {
		blkcg_clear_delay(lat_to_blkg(iolat));
		iolat->rq_depth.max_depth = UINT_MAX;
		wake_up_all(&iolat->rq_wait.wait);
		return;
	}

	scale_change(iolat, direction > 0);
}