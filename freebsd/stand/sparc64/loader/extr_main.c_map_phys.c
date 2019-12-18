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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int OF_call_method (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int) ; 
 int /*<<< orphan*/  mmu ; 

__attribute__((used)) static int
map_phys(int mode, size_t size, vm_offset_t virt, vm_offset_t phys)
{

	return (OF_call_method("map", mmu, 5, 0, (uint32_t)phys,
	    (uint32_t)(phys >> 32), virt, size, mode));
}