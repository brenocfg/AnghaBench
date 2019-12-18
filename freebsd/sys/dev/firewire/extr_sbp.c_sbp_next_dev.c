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
struct sbp_target {int num_lun; struct sbp_dev** luns; } ;
struct sbp_dev {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ SBP_DEV_PROBE ; 

__attribute__((used)) static struct sbp_dev *
sbp_next_dev(struct sbp_target *target, int lun)
{
	struct sbp_dev **sdevp;
	int i;

	for (i = lun, sdevp = &target->luns[lun]; i < target->num_lun;
	    i++, sdevp++)
		if (*sdevp != NULL && (*sdevp)->status == SBP_DEV_PROBE)
			return (*sdevp);
	return (NULL);
}