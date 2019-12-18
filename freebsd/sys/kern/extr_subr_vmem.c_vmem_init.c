#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bt_type; scalar_t__ bt_size; scalar_t__ bt_start; } ;
struct TYPE_13__ {int vm_quantum_mask; int /*<<< orphan*/  vm_hash0; int /*<<< orphan*/  vm_hashlist; int /*<<< orphan*/  vm_hashsize; int /*<<< orphan*/ * vm_freelist; TYPE_10__ vm_cursor; int /*<<< orphan*/  vm_seglist; scalar_t__ vm_inuse; scalar_t__ vm_limit; scalar_t__ vm_size; scalar_t__ vm_nbusytag; scalar_t__ vm_quantum_shift; int /*<<< orphan*/  vm_name; int /*<<< orphan*/  vm_freetags; scalar_t__ vm_nfreetags; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int vmem_size_t ;
typedef  int /*<<< orphan*/  vmem_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TYPE_CURSOR ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMEM_CONDVAR_INIT (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  VMEM_HASHSIZE_MIN ; 
 int /*<<< orphan*/  VMEM_LOCK_INIT (TYPE_1__*,char const*) ; 
 int VMEM_MAXORDER ; 
 int /*<<< orphan*/  bt_seglist ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ flsl (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qc_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vm_alllist ; 
 scalar_t__ vmem_add (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vmem_destroy1 (TYPE_1__*) ; 
 int /*<<< orphan*/  vmem_list ; 
 int /*<<< orphan*/  vmem_list_lock ; 

vmem_t *
vmem_init(vmem_t *vm, const char *name, vmem_addr_t base, vmem_size_t size,
    vmem_size_t quantum, vmem_size_t qcache_max, int flags)
{
	int i;

	MPASS(quantum > 0);
	MPASS((quantum & (quantum - 1)) == 0);

	bzero(vm, sizeof(*vm));

	VMEM_CONDVAR_INIT(vm, name);
	VMEM_LOCK_INIT(vm, name);
	vm->vm_nfreetags = 0;
	LIST_INIT(&vm->vm_freetags);
	strlcpy(vm->vm_name, name, sizeof(vm->vm_name));
	vm->vm_quantum_mask = quantum - 1;
	vm->vm_quantum_shift = flsl(quantum) - 1;
	vm->vm_nbusytag = 0;
	vm->vm_size = 0;
	vm->vm_limit = 0;
	vm->vm_inuse = 0;
	qc_init(vm, qcache_max);

	TAILQ_INIT(&vm->vm_seglist);
	vm->vm_cursor.bt_start = vm->vm_cursor.bt_size = 0;
	vm->vm_cursor.bt_type = BT_TYPE_CURSOR;
	TAILQ_INSERT_TAIL(&vm->vm_seglist, &vm->vm_cursor, bt_seglist);

	for (i = 0; i < VMEM_MAXORDER; i++)
		LIST_INIT(&vm->vm_freelist[i]);

	memset(&vm->vm_hash0, 0, sizeof(vm->vm_hash0));
	vm->vm_hashsize = VMEM_HASHSIZE_MIN;
	vm->vm_hashlist = vm->vm_hash0;

	if (size != 0) {
		if (vmem_add(vm, base, size, flags) != 0) {
			vmem_destroy1(vm);
			return NULL;
		}
	}

	mtx_lock(&vmem_list_lock);
	LIST_INSERT_HEAD(&vmem_list, vm, vm_alllist);
	mtx_unlock(&vmem_list_lock);

	return vm;
}