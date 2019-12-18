#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_8__ {int /*<<< orphan*/  pm_root; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_BITS_ALL ; 
 int vm_radix_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static __inline int
pmap_insert_pt_page(pmap_t pmap, vm_page_t ml3, bool promoted)
{

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	ml3->valid = promoted ? VM_PAGE_BITS_ALL : 0;
	return (vm_radix_insert(&pmap->pm_root, ml3));
}