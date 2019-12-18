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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pml4_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pm_pml4; } ;

/* Variables and functions */
 size_t pmap_pml4e_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline pml4_entry_t *
pmap_pml4e(pmap_t pmap, vm_offset_t va)
{

	return (&pmap->pm_pml4[pmap_pml4e_index(va)]);
}