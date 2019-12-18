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
typedef  int vmem_size_t ;
typedef  int /*<<< orphan*/  vmem_addr_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KVA_QUANTUM ; 
 int /*<<< orphan*/  VMEM_ADDR_MAX ; 
 int /*<<< orphan*/  VMEM_ADDR_MIN ; 
 int vmem_xalloc (void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kva_import_domain(void *arena, vmem_size_t size, int flags, vmem_addr_t *addrp)
{

	KASSERT((size % KVA_QUANTUM) == 0,
	    ("kva_import_domain: Size %jd is not a multiple of %d",
	    (intmax_t)size, (int)KVA_QUANTUM));
	return (vmem_xalloc(arena, size, KVA_QUANTUM, 0, 0, VMEM_ADDR_MIN,
	    VMEM_ADDR_MAX, flags, addrp));
}