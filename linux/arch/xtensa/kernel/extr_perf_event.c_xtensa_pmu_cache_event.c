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
 unsigned int ARRAY_SIZE (int***) ; 
 unsigned int C (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OP_MAX ; 
 int /*<<< orphan*/  RESULT_MAX ; 
 int*** xtensa_cache_ctl ; 

__attribute__((used)) static int xtensa_pmu_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_result;
	int ret;

	cache_type = (config >>  0) & 0xff;
	cache_op = (config >>  8) & 0xff;
	cache_result = (config >> 16) & 0xff;

	if (cache_type >= ARRAY_SIZE(xtensa_cache_ctl) ||
	    cache_op >= C(OP_MAX) ||
	    cache_result >= C(RESULT_MAX))
		return -EINVAL;

	ret = xtensa_cache_ctl[cache_type][cache_op][cache_result];

	if (ret == 0)
		return -EINVAL;

	return ret;
}