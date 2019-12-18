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
union hsw_tsx_tuning {scalar_t__ cycles_last_block; scalar_t__ value; } ;
typedef  scalar_t__ u64 ;

/* Variables and functions */

__attribute__((used)) static inline u64 intel_get_tsx_weight(u64 tsx_tuning)
{
	if (tsx_tuning) {
		union hsw_tsx_tuning tsx = { .value = tsx_tuning };
		return tsx.cycles_last_block;
	}
	return 0;
}