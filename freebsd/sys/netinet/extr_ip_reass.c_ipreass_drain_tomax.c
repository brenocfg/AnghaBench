#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipq {int dummy; } ;
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPQ_LOCK (int) ; 
 int /*<<< orphan*/  IPQ_UNLOCK (int) ; 
 int IPREASS_NHASH ; 
 struct ipq* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* V_ipq ; 
 int /*<<< orphan*/  V_ipq_zone ; 
 scalar_t__ V_ipreass_maxbucketsize ; 
 int /*<<< orphan*/  ipq_timeout (TYPE_1__*,struct ipq*) ; 
 int /*<<< orphan*/  ipqhead ; 
 int uma_zone_get_cur (int /*<<< orphan*/ ) ; 
 int uma_zone_get_max (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipreass_drain_tomax(void)
{
	struct ipq *fp;
	int target;

	/*
	 * Make sure each bucket is under the new limit. If
	 * necessary, drop enough of the oldest elements from
	 * each bucket to get under the new limit.
	 */
	for (int i = 0; i < IPREASS_NHASH; i++) {
		IPQ_LOCK(i);
		while (V_ipq[i].count > V_ipreass_maxbucketsize &&
		    (fp = TAILQ_LAST(&V_ipq[i].head, ipqhead)) != NULL)
			ipq_timeout(&V_ipq[i], fp);
		IPQ_UNLOCK(i);
	}

	/*
	 * If we are over the maximum number of fragments,
	 * drain off enough to get down to the new limit,
	 * stripping off last elements on queues.  Every
	 * run we strip the oldest element from each bucket.
	 */
	target = uma_zone_get_max(V_ipq_zone);
	while (uma_zone_get_cur(V_ipq_zone) > target) {
		for (int i = 0; i < IPREASS_NHASH; i++) {
			IPQ_LOCK(i);
			fp = TAILQ_LAST(&V_ipq[i].head, ipqhead);
			if (fp != NULL)
				ipq_timeout(&V_ipq[i], fp);
			IPQ_UNLOCK(i);
		}
	}
}