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
struct vm {int dummy; } ;
struct pptseg {scalar_t__ len; int /*<<< orphan*/  gpa; } ;
struct pptdev {struct pptseg* mmio; } ;

/* Variables and functions */
 int MAX_MMIOSEGS ; 
 int /*<<< orphan*/  bzero (struct pptseg*,int) ; 
 int /*<<< orphan*/  vm_unmap_mmio (struct vm*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ppt_unmap_mmio(struct vm *vm, struct pptdev *ppt)
{
	int i;
	struct pptseg *seg;

	for (i = 0; i < MAX_MMIOSEGS; i++) {
		seg = &ppt->mmio[i];
		if (seg->len == 0)
			continue;
		(void)vm_unmap_mmio(vm, seg->gpa, seg->len);
		bzero(seg, sizeof(struct pptseg));
	}
}