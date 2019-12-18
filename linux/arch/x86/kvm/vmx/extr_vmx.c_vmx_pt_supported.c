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

/* Variables and functions */
 scalar_t__ PT_MODE_HOST_GUEST ; 
 scalar_t__ pt_mode ; 

__attribute__((used)) static bool vmx_pt_supported(void)
{
	return pt_mode == PT_MODE_HOST_GUEST;
}