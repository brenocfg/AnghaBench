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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_enabled_hcalls ; 
 int* default_hcall_list ; 
 int /*<<< orphan*/  kvmppc_hcall_impl_hv (unsigned int) ; 

__attribute__((used)) static void init_default_hcalls(void)
{
	int i;
	unsigned int hcall;

	for (i = 0; default_hcall_list[i]; ++i) {
		hcall = default_hcall_list[i];
		WARN_ON(!kvmppc_hcall_impl_hv(hcall));
		__set_bit(hcall / 4, default_enabled_hcalls);
	}
}