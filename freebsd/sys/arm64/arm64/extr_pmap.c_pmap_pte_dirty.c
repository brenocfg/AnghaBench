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
typedef  int pt_entry_t ;

/* Variables and functions */
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RW ; 
 int ATTR_AP_RW_BIT ; 
 int ATTR_SW_DBM ; 
 int ATTR_SW_MANAGED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static inline int
pmap_pte_dirty(pt_entry_t pte)
{

	KASSERT((pte & ATTR_SW_MANAGED) != 0, ("pte %#lx is unmanaged", pte));
	KASSERT((pte & (ATTR_AP_RW_BIT | ATTR_SW_DBM)) != 0,
	    ("pte %#lx is writeable and missing ATTR_SW_DBM", pte));

	return ((pte & (ATTR_AP_RW_BIT | ATTR_SW_DBM)) ==
	    (ATTR_AP(ATTR_AP_RW) | ATTR_SW_DBM));
}