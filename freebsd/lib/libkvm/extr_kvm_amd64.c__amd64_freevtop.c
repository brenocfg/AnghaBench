#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmstate {struct vmstate* phdr; struct vmstate* PML4; } ;
struct TYPE_3__ {struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vmstate*) ; 

__attribute__((used)) static void
_amd64_freevtop(kvm_t *kd)
{
	struct vmstate *vm = kd->vmst;

	if (vm->PML4)
		free(vm->PML4);
	free(vm->phdr);
	free(vm);
	kd->vmst = NULL;
}