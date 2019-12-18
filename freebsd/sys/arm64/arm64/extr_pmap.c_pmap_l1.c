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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int L0_TABLE ; 
 int /*<<< orphan*/ * pmap_l0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l0_to_l1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline pd_entry_t *
pmap_l1(pmap_t pmap, vm_offset_t va)
{
	pd_entry_t *l0;

	l0 = pmap_l0(pmap, va);
	if ((pmap_load(l0) & ATTR_DESCR_MASK) != L0_TABLE)
		return (NULL);

	return (pmap_l0_to_l1(l0, va));
}