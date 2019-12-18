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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  nregs; int /*<<< orphan*/  nfree; } ;
typedef  TYPE_1__ extent_util_stats_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extent_util_stats_get (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
experimental_utilization_batch_query_ctl(tsd_t *tsd, const size_t *mib,
    size_t miblen, void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;

	assert(sizeof(extent_util_stats_t) == sizeof(size_t) * 3);

	const size_t len = newlen / sizeof(const void *);
	if (oldp == NULL || oldlenp == NULL || newp == NULL || newlen == 0
	    || newlen != len * sizeof(const void *)
	    || *oldlenp != len * sizeof(extent_util_stats_t)) {
		ret = EINVAL;
		goto label_return;
	}

	void **ptrs = (void **)newp;
	extent_util_stats_t *util_stats = (extent_util_stats_t *)oldp;
	size_t i;
	for (i = 0; i < len; ++i) {
		extent_util_stats_get(tsd_tsdn(tsd), ptrs[i],
		    &util_stats[i].nfree, &util_stats[i].nregs,
		    &util_stats[i].size);
	}
	ret = 0;

label_return:
	return ret;
}