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
struct ccu_frac_internal {unsigned long* rates; } ;
struct ccu_common {int features; } ;

/* Variables and functions */
 int CCU_FEATURE_FRACTIONAL ; 

bool ccu_frac_helper_has_rate(struct ccu_common *common,
			      struct ccu_frac_internal *cf,
			      unsigned long rate)
{
	if (!(common->features & CCU_FEATURE_FRACTIONAL))
		return false;

	return (cf->rates[0] == rate) || (cf->rates[1] == rate);
}