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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ max_depth; } ;
struct iolatency_grp {scalar_t__ min_lat_nsec; TYPE_1__ rq_depth; } ;
struct bio_issue {int dummy; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 scalar_t__ __bio_issue_time (scalar_t__) ; 
 scalar_t__ bio_issue_time (struct bio_issue*) ; 
 int /*<<< orphan*/  blkcg_add_delay (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lat_to_blkg (struct iolatency_grp*) ; 
 int /*<<< orphan*/  latency_stat_record_time (struct iolatency_grp*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void iolatency_record_time(struct iolatency_grp *iolat,
				  struct bio_issue *issue, u64 now,
				  bool issue_as_root)
{
	u64 start = bio_issue_time(issue);
	u64 req_time;

	/*
	 * Have to do this so we are truncated to the correct time that our
	 * issue is truncated to.
	 */
	now = __bio_issue_time(now);

	if (now <= start)
		return;

	req_time = now - start;

	/*
	 * We don't want to count issue_as_root bio's in the cgroups latency
	 * statistics as it could skew the numbers downwards.
	 */
	if (unlikely(issue_as_root && iolat->rq_depth.max_depth != UINT_MAX)) {
		u64 sub = iolat->min_lat_nsec;
		if (req_time < sub)
			blkcg_add_delay(lat_to_blkg(iolat), now, sub - req_time);
		return;
	}

	latency_stat_record_time(iolat, req_time);
}