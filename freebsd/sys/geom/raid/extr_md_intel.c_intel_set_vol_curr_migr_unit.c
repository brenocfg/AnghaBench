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
struct intel_raid_vol {int curr_migr_unit; int curr_migr_unit_hi; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static void
intel_set_vol_curr_migr_unit(struct intel_raid_vol *vol, off_t curr_migr_unit)
{

	vol->curr_migr_unit = curr_migr_unit & 0xffffffff;
	vol->curr_migr_unit_hi = curr_migr_unit >> 32;
}