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
struct vmspace {int dummy; } ;
struct vm {int sockets; int /*<<< orphan*/  maxcpus; int /*<<< orphan*/  threads; int /*<<< orphan*/  cores; int /*<<< orphan*/  rendezvous_mtx; struct vmspace* vmspace; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_VM ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct vmspace* VMSPACE_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAXCPU ; 
 int /*<<< orphan*/  VM_MAXUSER_ADDRESS ; 
 scalar_t__ VM_MAX_NAMELEN ; 
 int /*<<< orphan*/  cores_per_package ; 
 struct vm* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  threads_per_core ; 
 int /*<<< orphan*/  vm_init (struct vm*,int) ; 
 int /*<<< orphan*/  vmm_initialized ; 

int
vm_create(const char *name, struct vm **retvm)
{
	struct vm *vm;
	struct vmspace *vmspace;

	/*
	 * If vmm.ko could not be successfully initialized then don't attempt
	 * to create the virtual machine.
	 */
	if (!vmm_initialized)
		return (ENXIO);

	if (name == NULL || strlen(name) >= VM_MAX_NAMELEN)
		return (EINVAL);

	vmspace = VMSPACE_ALLOC(0, VM_MAXUSER_ADDRESS);
	if (vmspace == NULL)
		return (ENOMEM);

	vm = malloc(sizeof(struct vm), M_VM, M_WAITOK | M_ZERO);
	strcpy(vm->name, name);
	vm->vmspace = vmspace;
	mtx_init(&vm->rendezvous_mtx, "vm rendezvous lock", 0, MTX_DEF);

	vm->sockets = 1;
	vm->cores = cores_per_package;	/* XXX backwards compatibility */
	vm->threads = threads_per_core;	/* XXX backwards compatibility */
	vm->maxcpus = VM_MAXCPU;	/* XXX temp to keep code working */

	vm_init(vm, true);

	*retvm = vm;
	return (0);
}