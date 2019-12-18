#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct rq_wb {int /*<<< orphan*/  sync_cookie; int /*<<< orphan*/  sync_issue; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 rwb_sync_issue_lat(struct rq_wb *rwb)
{
	u64 now, issue = READ_ONCE(rwb->sync_issue);

	if (!issue || !rwb->sync_cookie)
		return 0;

	now = ktime_to_ns(ktime_get());
	return now - issue;
}