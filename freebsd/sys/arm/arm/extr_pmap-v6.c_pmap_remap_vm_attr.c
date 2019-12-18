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
typedef  scalar_t__ vm_memattr_t ;

/* Variables and functions */
 int PTE2_ATTR2IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_set_tex () ; 
 int /*<<< orphan*/ * pte2_attr_tab ; 
 int /*<<< orphan*/ * tex_class ; 

void
pmap_remap_vm_attr(vm_memattr_t old_attr, vm_memattr_t new_attr)
{
	int old_idx, new_idx;

	/* Map VM memattrs to indexes to tex_class table. */
	old_idx = PTE2_ATTR2IDX(pte2_attr_tab[(int)old_attr]);
	new_idx = PTE2_ATTR2IDX(pte2_attr_tab[(int)new_attr]);

	/* Replace TEX attribute and apply it. */
	tex_class[old_idx] = tex_class[new_idx];
	pmap_set_tex();
}