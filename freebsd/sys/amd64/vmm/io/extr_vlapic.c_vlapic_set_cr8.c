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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlapic_set_tpr (struct vlapic*,int) ; 
 int /*<<< orphan*/  vm_inject_gp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vlapic_set_cr8(struct vlapic *vlapic, uint64_t val)
{
	uint8_t tpr;

	if (val & ~0xf) {
		vm_inject_gp(vlapic->vm, vlapic->vcpuid);
		return;
	}

	tpr = val << 4;
	vlapic_set_tpr(vlapic, tpr);
}