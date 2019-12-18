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
 int VMX_BITMAP_NR ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__* vmx_bitmap ; 

void nested_vmx_hardware_unsetup(void)
{
	int i;

	if (enable_shadow_vmcs) {
		for (i = 0; i < VMX_BITMAP_NR; i++)
			free_page((unsigned long)vmx_bitmap[i]);
	}
}