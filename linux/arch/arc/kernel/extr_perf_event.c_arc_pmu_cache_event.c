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
typedef  int u64 ;

/* Variables and functions */
 int CACHE_OP_UNSUPPORTED ; 
 int EINVAL ; 
 int ENOENT ; 
 unsigned int PERF_COUNT_HW_CACHE_MAX ; 
 unsigned int PERF_COUNT_HW_CACHE_OP_MAX ; 
 unsigned int PERF_COUNT_HW_CACHE_RESULT_MAX ; 
 int*** arc_pmu_cache_map ; 
 int /*<<< orphan*/ * arc_pmu_ev_hw_map ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arc_pmu_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_result;
	int ret;

	cache_type	= (config >>  0) & 0xff;
	cache_op	= (config >>  8) & 0xff;
	cache_result	= (config >> 16) & 0xff;
	if (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		return -EINVAL;
	if (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		return -EINVAL;
	if (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		return -EINVAL;

	ret = arc_pmu_cache_map[cache_type][cache_op][cache_result];

	if (ret == CACHE_OP_UNSUPPORTED)
		return -ENOENT;

	pr_debug("init cache event: type/op/result %d/%d/%d with h/w %d \'%s\'\n",
		 cache_type, cache_op, cache_result, ret,
		 arc_pmu_ev_hw_map[ret]);

	return ret;
}