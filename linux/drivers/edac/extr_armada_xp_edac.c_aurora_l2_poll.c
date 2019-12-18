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
struct edac_device_ctl_info {struct aurora_l2_drvdata* pvt_info; } ;
struct aurora_l2_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aurora_l2_check (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  aurora_l2_inject (struct aurora_l2_drvdata*) ; 

__attribute__((used)) static void aurora_l2_poll(struct edac_device_ctl_info *dci)
{
#ifdef CONFIG_EDAC_DEBUG
	struct aurora_l2_drvdata *drvdata = dci->pvt_info;
#endif

	aurora_l2_check(dci);
#ifdef CONFIG_EDAC_DEBUG
	aurora_l2_inject(drvdata);
#endif
}