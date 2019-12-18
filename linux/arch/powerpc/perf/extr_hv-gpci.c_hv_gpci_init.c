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
struct hv_perf_caps {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  PERF_PMU_CAP_NO_INTERRUPT ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__ h_gpci_pmu ; 
 int /*<<< orphan*/  hv_gpci_assert_offsets_correct () ; 
 unsigned long hv_perf_caps_get (struct hv_perf_caps*) ; 
 int perf_pmu_register (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int hv_gpci_init(void)
{
	int r;
	unsigned long hret;
	struct hv_perf_caps caps;

	hv_gpci_assert_offsets_correct();

	if (!firmware_has_feature(FW_FEATURE_LPAR)) {
		pr_debug("not a virtualized system, not enabling\n");
		return -ENODEV;
	}

	hret = hv_perf_caps_get(&caps);
	if (hret) {
		pr_debug("could not obtain capabilities, not enabling, rc=%ld\n",
				hret);
		return -ENODEV;
	}

	/* sampling not supported */
	h_gpci_pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

	r = perf_pmu_register(&h_gpci_pmu, h_gpci_pmu.name, -1);
	if (r)
		return r;

	return 0;
}