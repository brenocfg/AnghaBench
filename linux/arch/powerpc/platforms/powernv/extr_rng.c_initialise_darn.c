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
struct TYPE_2__ {scalar_t__ (* get_random_seed ) (unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ powernv_get_random_darn (unsigned long*) ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int initialise_darn(void)
{
	unsigned long val;
	int i;

	if (!cpu_has_feature(CPU_FTR_ARCH_300))
		return -ENODEV;

	for (i = 0; i < 10; i++) {
		if (powernv_get_random_darn(&val)) {
			ppc_md.get_random_seed = powernv_get_random_darn;
			return 0;
		}
	}

	pr_warn("Unable to use DARN for get_random_seed()\n");

	return -EIO;
}