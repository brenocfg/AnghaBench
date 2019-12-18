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
struct vm_special_mapping {int dummy; } ;
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_VDSO ; 
 int __vdso_remap (int /*<<< orphan*/ ,struct vm_special_mapping const*,struct vm_area_struct*) ; 

__attribute__((used)) static int vdso_mremap(const struct vm_special_mapping *sm,
		struct vm_area_struct *new_vma)
{
	return __vdso_remap(ARM64_VDSO, sm, new_vma);
}