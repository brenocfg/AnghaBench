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
typedef  enum rdtgrp_mode { ____Placeholder_rdtgrp_mode } rdtgrp_mode ;

/* Variables and functions */
 int RDT_MODE_SHAREABLE ; 
 int RDT_NUM_MODES ; 
 char const** rdt_mode_str ; 

__attribute__((used)) static const char *rdtgroup_mode_str(enum rdtgrp_mode mode)
{
	if (mode < RDT_MODE_SHAREABLE || mode >= RDT_NUM_MODES)
		return "unknown";

	return rdt_mode_str[mode];
}