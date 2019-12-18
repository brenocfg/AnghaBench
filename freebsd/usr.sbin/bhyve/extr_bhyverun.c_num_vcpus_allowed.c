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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSP ; 
 int /*<<< orphan*/  VM_CAP_UNRESTRICTED_GUEST ; 
 int VM_MAXCPU ; 
 int vm_get_capability (struct vmctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
num_vcpus_allowed(struct vmctx *ctx)
{
	int tmp, error;

	error = vm_get_capability(ctx, BSP, VM_CAP_UNRESTRICTED_GUEST, &tmp);

	/*
	 * The guest is allowed to spinup more than one processor only if the
	 * UNRESTRICTED_GUEST capability is available.
	 */
	if (error == 0)
		return (VM_MAXCPU);
	else
		return (1);
}