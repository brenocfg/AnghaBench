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
typedef  int /*<<< orphan*/  vmem_t ;
typedef  int /*<<< orphan*/  vmem_size_t ;
typedef  int /*<<< orphan*/  vmem_addr_t ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/ * uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vmem_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmem_zone ; 

vmem_t *
vmem_create(const char *name, vmem_addr_t base, vmem_size_t size,
    vmem_size_t quantum, vmem_size_t qcache_max, int flags)
{

	vmem_t *vm;

	vm = uma_zalloc(vmem_zone, flags & (M_WAITOK|M_NOWAIT));
	if (vm == NULL)
		return (NULL);
	if (vmem_init(vm, name, base, size, quantum, qcache_max,
	    flags) == NULL)
		return (NULL);
	return (vm);
}