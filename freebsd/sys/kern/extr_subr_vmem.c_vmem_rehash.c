#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vm_hashsize; struct vmem_hashlist* vm_hash0; struct vmem_hashlist* vm_hashlist; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int vmem_size_t ;
struct vmem_hashlist {int dummy; } ;
typedef  int /*<<< orphan*/  bt_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * LIST_FIRST (struct vmem_hashlist*) ; 
 int /*<<< orphan*/  LIST_INIT (struct vmem_hashlist*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_VMEM ; 
 int /*<<< orphan*/  VMEM_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_insbusy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_rembusy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct vmem_hashlist*,int /*<<< orphan*/ ) ; 
 struct vmem_hashlist* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmem_rehash(vmem_t *vm, vmem_size_t newhashsize)
{
	bt_t *bt;
	int i;
	struct vmem_hashlist *newhashlist;
	struct vmem_hashlist *oldhashlist;
	vmem_size_t oldhashsize;

	MPASS(newhashsize > 0);

	newhashlist = malloc(sizeof(struct vmem_hashlist) * newhashsize,
	    M_VMEM, M_NOWAIT);
	if (newhashlist == NULL)
		return ENOMEM;
	for (i = 0; i < newhashsize; i++) {
		LIST_INIT(&newhashlist[i]);
	}

	VMEM_LOCK(vm);
	oldhashlist = vm->vm_hashlist;
	oldhashsize = vm->vm_hashsize;
	vm->vm_hashlist = newhashlist;
	vm->vm_hashsize = newhashsize;
	if (oldhashlist == NULL) {
		VMEM_UNLOCK(vm);
		return 0;
	}
	for (i = 0; i < oldhashsize; i++) {
		while ((bt = LIST_FIRST(&oldhashlist[i])) != NULL) {
			bt_rembusy(vm, bt);
			bt_insbusy(vm, bt);
		}
	}
	VMEM_UNLOCK(vm);

	if (oldhashlist != vm->vm_hash0) {
		free(oldhashlist, M_VMEM);
	}

	return 0;
}