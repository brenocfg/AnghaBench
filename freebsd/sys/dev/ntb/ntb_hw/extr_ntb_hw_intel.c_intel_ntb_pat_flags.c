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
typedef  int /*<<< orphan*/  vm_memattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WEAK_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_PROTECTED ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_THROUGH ; 
#define  _NTB_PAT_UC 133 
#define  _NTB_PAT_UCM 132 
#define  _NTB_PAT_WB 131 
#define  _NTB_PAT_WC 130 
#define  _NTB_PAT_WP 129 
#define  _NTB_PAT_WT 128 
 int g_ntb_mw_pat ; 

__attribute__((used)) static inline vm_memattr_t
intel_ntb_pat_flags(void)
{

	switch (g_ntb_mw_pat) {
	case _NTB_PAT_WC:
		return (VM_MEMATTR_WRITE_COMBINING);
	case _NTB_PAT_WT:
		return (VM_MEMATTR_WRITE_THROUGH);
	case _NTB_PAT_WP:
		return (VM_MEMATTR_WRITE_PROTECTED);
	case _NTB_PAT_WB:
		return (VM_MEMATTR_WRITE_BACK);
	case _NTB_PAT_UCM:
		return (VM_MEMATTR_WEAK_UNCACHEABLE);
	case _NTB_PAT_UC:
		/* FALLTHROUGH */
	default:
		return (VM_MEMATTR_UNCACHEABLE);
	}
}