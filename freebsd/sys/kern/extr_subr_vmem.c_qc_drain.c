#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vm_qcache_max; int vm_quantum_shift; TYPE_1__* vm_qcache; } ;
typedef  TYPE_2__ vmem_t ;
struct TYPE_4__ {int /*<<< orphan*/  qc_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_RECLAIM_DRAIN ; 
 int /*<<< orphan*/  uma_zone_reclaim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qc_drain(vmem_t *vm)
{
	int qcache_idx_max;
	int i;

	qcache_idx_max = vm->vm_qcache_max >> vm->vm_quantum_shift;
	for (i = 0; i < qcache_idx_max; i++)
		uma_zone_reclaim(vm->vm_qcache[i].qc_cache, UMA_RECLAIM_DRAIN);
}