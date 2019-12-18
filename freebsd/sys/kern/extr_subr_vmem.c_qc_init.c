#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vm_quantum_mask; int vm_quantum_shift; int vm_qcache_max; char* vm_name; TYPE_2__* vm_qcache; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int vmem_size_t ;
struct TYPE_6__ {int qc_size; int qc_cache; int /*<<< orphan*/  qc_name; TYPE_1__* qc_vmem; } ;
typedef  TYPE_2__ qcache_t ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  UMA_ZONE_VM ; 
 int /*<<< orphan*/  VMEM_QCACHE_IDX_MAX ; 
 int /*<<< orphan*/  qc_import ; 
 int /*<<< orphan*/  qc_release ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int uma_zcache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qc_init(vmem_t *vm, vmem_size_t qcache_max)
{
	qcache_t *qc;
	vmem_size_t size;
	int qcache_idx_max;
	int i;

	MPASS((qcache_max & vm->vm_quantum_mask) == 0);
	qcache_idx_max = MIN(qcache_max >> vm->vm_quantum_shift,
	    VMEM_QCACHE_IDX_MAX);
	vm->vm_qcache_max = qcache_idx_max << vm->vm_quantum_shift;
	for (i = 0; i < qcache_idx_max; i++) {
		qc = &vm->vm_qcache[i];
		size = (i + 1) << vm->vm_quantum_shift;
		snprintf(qc->qc_name, sizeof(qc->qc_name), "%s-%zu",
		    vm->vm_name, size);
		qc->qc_vmem = vm;
		qc->qc_size = size;
		qc->qc_cache = uma_zcache_create(qc->qc_name, size,
		    NULL, NULL, NULL, NULL, qc_import, qc_release, qc,
		    UMA_ZONE_VM);
		MPASS(qc->qc_cache);
	}
}