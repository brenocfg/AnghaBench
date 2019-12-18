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
struct cuse_memory {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CUSE ; 
 int /*<<< orphan*/  free (struct cuse_memory*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cuse_vm_memory_free(struct cuse_memory *mem)
{
	/* last user is gone - free */
	vm_object_deallocate(mem->object);

	/* free CUSE memory */
	free(mem, M_CUSE);
}