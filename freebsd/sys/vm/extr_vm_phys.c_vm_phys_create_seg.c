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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  _vm_phys_create_seg (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* mem_affinity ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static void
vm_phys_create_seg(vm_paddr_t start, vm_paddr_t end)
{
#ifdef NUMA
	int i;

	if (mem_affinity == NULL) {
		_vm_phys_create_seg(start, end, 0);
		return;
	}

	for (i = 0;; i++) {
		if (mem_affinity[i].end == 0)
			panic("Reached end of affinity info");
		if (mem_affinity[i].end <= start)
			continue;
		if (mem_affinity[i].start > start)
			panic("No affinity info for start %jx",
			    (uintmax_t)start);
		if (mem_affinity[i].end >= end) {
			_vm_phys_create_seg(start, end,
			    mem_affinity[i].domain);
			break;
		}
		_vm_phys_create_seg(start, mem_affinity[i].end,
		    mem_affinity[i].domain);
		start = mem_affinity[i].end;
	}
#else
	_vm_phys_create_seg(start, end, 0);
#endif
}