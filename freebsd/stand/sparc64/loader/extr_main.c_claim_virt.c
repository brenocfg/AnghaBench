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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int OF_call_method (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu ; 

__attribute__((used)) static vm_offset_t
claim_virt(vm_offset_t virt, size_t size, int align)
{
	vm_offset_t mva;

	if (OF_call_method("claim", mmu, 3, 1, virt, size, align, &mva) == -1)
		return ((vm_offset_t)-1);
	return (mva);
}