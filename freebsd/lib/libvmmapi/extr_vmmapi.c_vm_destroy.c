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
struct vmctx {scalar_t__ fd; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct vmctx*) ; 

void
vm_destroy(struct vmctx *vm)
{
	assert(vm != NULL);

	if (vm->fd >= 0)
		close(vm->fd);
	DESTROY(vm->name);

	free(vm);
}