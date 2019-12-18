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
struct nds32_pmu {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  device_pmu_init (struct nds32_pmu*) ; 
 int /*<<< orphan*/  get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static int probe_current_pmu(struct nds32_pmu *pmu)
{
	int ret;

	get_cpu();
	ret = -ENODEV;
	/*
	 * If ther are various CPU types with its own PMU, initialize with
	 *
	 * the corresponding one
	 */
	device_pmu_init(pmu);
	put_cpu();
	return ret;
}