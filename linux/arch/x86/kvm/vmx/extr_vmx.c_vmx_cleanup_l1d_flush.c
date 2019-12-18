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
 int /*<<< orphan*/  L1D_CACHE_ORDER ; 
 int /*<<< orphan*/  VMENTER_L1D_FLUSH_AUTO ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l1tf_vmx_mitigation ; 
 int /*<<< orphan*/ * vmx_l1d_flush_pages ; 

__attribute__((used)) static void vmx_cleanup_l1d_flush(void)
{
	if (vmx_l1d_flush_pages) {
		free_pages((unsigned long)vmx_l1d_flush_pages, L1D_CACHE_ORDER);
		vmx_l1d_flush_pages = NULL;
	}
	/* Restore state so sysfs ignores VMX */
	l1tf_vmx_mitigation = VMENTER_L1D_FLUSH_AUTO;
}