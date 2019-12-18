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
struct ecore_dev {int recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_dev*,char*,char*) ; 

void ecore_set_dev_access_enable(struct ecore_dev *p_dev, bool b_enable)
{
	if (p_dev->recov_in_prog != !b_enable) {
		DP_INFO(p_dev, "%s access to the device\n",
			b_enable ?  "Enable" : "Disable");
		p_dev->recov_in_prog = !b_enable;
	}
}