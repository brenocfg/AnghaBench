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
struct loaded_vmcs {int cpu; scalar_t__ launched; scalar_t__ shadow_vmcs; scalar_t__ vmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmcs_clear (scalar_t__) ; 

void loaded_vmcs_init(struct loaded_vmcs *loaded_vmcs)
{
	vmcs_clear(loaded_vmcs->vmcs);
	if (loaded_vmcs->shadow_vmcs && loaded_vmcs->launched)
		vmcs_clear(loaded_vmcs->shadow_vmcs);
	loaded_vmcs->cpu = -1;
	loaded_vmcs->launched = 0;
}