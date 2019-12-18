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
struct TYPE_2__ {unsigned long* pmc_count_shift; unsigned long* pmc_count_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERFMON_CMD_READ ; 
 TYPE_1__* alpha_pmu ; 
 unsigned long wrperfmon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long alpha_read_pmc(int idx)
{
	unsigned long val;

	val = wrperfmon(PERFMON_CMD_READ, 0);
	val >>= alpha_pmu->pmc_count_shift[idx];
	val &= alpha_pmu->pmc_count_mask[idx];
	return val;
}