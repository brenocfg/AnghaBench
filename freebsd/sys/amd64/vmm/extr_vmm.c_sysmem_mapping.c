#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm {TYPE_1__* mem_segs; } ;
struct mem_map {scalar_t__ len; size_t segid; } ;
struct TYPE_2__ {scalar_t__ sysmem; } ;

/* Variables and functions */

__attribute__((used)) static __inline bool
sysmem_mapping(struct vm *vm, struct mem_map *mm)
{

	if (mm->len != 0 && vm->mem_segs[mm->segid].sysmem)
		return (true);
	else
		return (false);
}