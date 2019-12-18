#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cpu_user_features2; int /*<<< orphan*/  oprofile_cpu_type; } ;
struct TYPE_4__ {void* n_blacklist_ev; void* blacklist_ev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  PPC_FEATURE2_EBB ; 
 int PVR_CFG (unsigned int) ; 
 int PVR_MIN (unsigned int) ; 
 unsigned int PVR_POWER9_CUMULUS ; 
 int /*<<< orphan*/  SPRN_PVR ; 
 TYPE_3__* cur_cpu_spec ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 void* p9_dd21_bl_ev ; 
 void* p9_dd22_bl_ev ; 
 TYPE_1__ power9_pmu ; 
 int register_power_pmu (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int init_power9_pmu(void)
{
	int rc = 0;
	unsigned int pvr = mfspr(SPRN_PVR);

	/* Comes from cpu_specs[] */
	if (!cur_cpu_spec->oprofile_cpu_type ||
	    strcmp(cur_cpu_spec->oprofile_cpu_type, "ppc64/power9"))
		return -ENODEV;

	/* Blacklist events */
	if (!(pvr & PVR_POWER9_CUMULUS)) {
		if ((PVR_CFG(pvr) == 2) && (PVR_MIN(pvr) == 1)) {
			power9_pmu.blacklist_ev = p9_dd21_bl_ev;
			power9_pmu.n_blacklist_ev = ARRAY_SIZE(p9_dd21_bl_ev);
		} else if ((PVR_CFG(pvr) == 2) && (PVR_MIN(pvr) == 2)) {
			power9_pmu.blacklist_ev = p9_dd22_bl_ev;
			power9_pmu.n_blacklist_ev = ARRAY_SIZE(p9_dd22_bl_ev);
		}
	}

	rc = register_power_pmu(&power9_pmu);
	if (rc)
		return rc;

	/* Tell userspace that EBB is supported */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_EBB;

	return 0;
}