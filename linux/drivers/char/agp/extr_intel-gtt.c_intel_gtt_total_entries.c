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
struct TYPE_2__ {unsigned int gtt_mappable_entries; } ;

/* Variables and functions */
 int INTEL_GTT_GEN ; 
 scalar_t__ IS_G33 ; 
 unsigned int i965_gtt_total_entries () ; 
 TYPE_1__ intel_private ; 

__attribute__((used)) static unsigned int intel_gtt_total_entries(void)
{
	if (IS_G33 || INTEL_GTT_GEN == 4 || INTEL_GTT_GEN == 5)
		return i965_gtt_total_entries();
	else {
		/* On previous hardware, the GTT size was just what was
		 * required to map the aperture.
		 */
		return intel_private.gtt_mappable_entries;
	}
}