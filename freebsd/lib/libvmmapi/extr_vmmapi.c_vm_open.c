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
struct vmctx {int fd; int lowmem_limit; char* name; scalar_t__ memflags; } ;

/* Variables and functions */
 int GB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct vmctx* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vm_destroy (struct vmctx*) ; 
 int vm_device_open (char*) ; 

struct vmctx *
vm_open(const char *name)
{
	struct vmctx *vm;

	vm = malloc(sizeof(struct vmctx) + strlen(name) + 1);
	assert(vm != NULL);

	vm->fd = -1;
	vm->memflags = 0;
	vm->lowmem_limit = 3 * GB;
	vm->name = (char *)(vm + 1);
	strcpy(vm->name, name);

	if ((vm->fd = vm_device_open(vm->name)) < 0)
		goto err;

	return (vm);
err:
	vm_destroy(vm);
	return (NULL);
}