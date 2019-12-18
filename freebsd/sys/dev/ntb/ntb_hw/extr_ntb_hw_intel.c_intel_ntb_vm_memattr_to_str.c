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
typedef  int vm_memattr_t ;

/* Variables and functions */
#define  VM_MEMATTR_UNCACHEABLE 133 
#define  VM_MEMATTR_WEAK_UNCACHEABLE 132 
#define  VM_MEMATTR_WRITE_BACK 131 
#define  VM_MEMATTR_WRITE_COMBINING 130 
#define  VM_MEMATTR_WRITE_PROTECTED 129 
#define  VM_MEMATTR_WRITE_THROUGH 128 

__attribute__((used)) static inline const char *
intel_ntb_vm_memattr_to_str(vm_memattr_t pat)
{

	switch (pat) {
	case VM_MEMATTR_WRITE_COMBINING:
		return ("WRITE_COMBINING");
	case VM_MEMATTR_WRITE_THROUGH:
		return ("WRITE_THROUGH");
	case VM_MEMATTR_WRITE_PROTECTED:
		return ("WRITE_PROTECTED");
	case VM_MEMATTR_WRITE_BACK:
		return ("WRITE_BACK");
	case VM_MEMATTR_WEAK_UNCACHEABLE:
		return ("UNCACHED");
	case VM_MEMATTR_UNCACHEABLE:
		return ("UNCACHEABLE");
	default:
		return ("UNKNOWN");
	}
}