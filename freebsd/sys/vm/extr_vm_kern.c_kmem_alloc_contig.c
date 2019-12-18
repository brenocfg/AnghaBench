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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_RR () ; 
 int /*<<< orphan*/  kmem_alloc_contig_domainset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vm_offset_t
kmem_alloc_contig(vm_size_t size, int flags, vm_paddr_t low, vm_paddr_t high,
    u_long alignment, vm_paddr_t boundary, vm_memattr_t memattr)
{

	return (kmem_alloc_contig_domainset(DOMAINSET_RR(), size, flags, low,
	    high, alignment, boundary, memattr));
}