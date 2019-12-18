#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {int /*<<< orphan*/  pm_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int PDRSHIFT ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_radix_remove (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline vm_page_t
pmap_remove_pt_page(pmap_t pmap, vm_offset_t va)
{

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	return (vm_radix_remove(&pmap->pm_root, va >> PDRSHIFT));
}