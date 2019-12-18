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
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_ACTIVE_CPUS ; 
 int vm_get_cpus (struct vmctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
vm_active_cpus(struct vmctx *ctx, cpuset_t *cpus)
{

	return (vm_get_cpus(ctx, VM_ACTIVE_CPUS, cpus));
}