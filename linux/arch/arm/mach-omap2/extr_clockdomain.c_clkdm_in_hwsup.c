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
struct clockdomain {int _flags; } ;

/* Variables and functions */
 int _CLKDM_FLAG_HWSUP_ENABLED ; 

bool clkdm_in_hwsup(struct clockdomain *clkdm)
{
	bool ret;

	if (!clkdm)
		return false;

	ret = (clkdm->_flags & _CLKDM_FLAG_HWSUP_ENABLED) ? true : false;

	return ret;
}