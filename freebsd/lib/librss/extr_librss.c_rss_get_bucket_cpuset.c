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
struct rss_config {int rss_nbuckets; int /*<<< orphan*/ * rss_bucket_map; } ;
typedef  scalar_t__ rss_bucket_type_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 scalar_t__ RSS_BUCKET_TYPE_MAX ; 
 scalar_t__ RSS_BUCKET_TYPE_NONE ; 
 int /*<<< orphan*/  errno ; 

int
rss_get_bucket_cpuset(struct rss_config *rc, rss_bucket_type_t btype,
    int bucket, cpuset_t *cs)
{

	if (bucket < 0 || bucket >= rc->rss_nbuckets) {
		errno = EINVAL;
		return (-1);
	}

	/*
	 * For now all buckets are the same, but eventually we'll want
	 * to allow administrators to set separate RSS cpusets for
	 * {kernel,user} {tx, rx} combinations.
	 */
	if (btype <= RSS_BUCKET_TYPE_NONE || btype > RSS_BUCKET_TYPE_MAX) {
		errno = ENOTSUP;
		return (-1);
	}

	CPU_ZERO(cs);
	CPU_SET(rc->rss_bucket_map[bucket], cs);

	return (0);
}