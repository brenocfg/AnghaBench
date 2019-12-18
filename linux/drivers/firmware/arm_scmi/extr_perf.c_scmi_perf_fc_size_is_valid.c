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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ PERF_LEVEL_GET ; 
 scalar_t__ PERF_LEVEL_SET ; 
 scalar_t__ PERF_LIMITS_GET ; 
 scalar_t__ PERF_LIMITS_SET ; 

__attribute__((used)) static bool scmi_perf_fc_size_is_valid(u32 msg, u32 size)
{
	if ((msg == PERF_LEVEL_GET || msg == PERF_LEVEL_SET) && size == 4)
		return true;
	if ((msg == PERF_LIMITS_GET || msg == PERF_LIMITS_SET) && size == 8)
		return true;
	return false;
}