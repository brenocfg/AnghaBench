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
typedef  int pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ pm_type; int pm_flags; } ;

/* Variables and functions */
 int EPT_PG_EXECUTE ; 
 int EPT_PG_WRITE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PMAP_SUPPORTS_EXEC_ONLY ; 
 scalar_t__ PT_EPT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pmap_emulate_ad_bits (TYPE_1__*) ; 

__attribute__((used)) static __inline boolean_t
safe_to_clear_referenced(pmap_t pmap, pt_entry_t pte)
{

	if (!pmap_emulate_ad_bits(pmap))
		return (TRUE);

	KASSERT(pmap->pm_type == PT_EPT, ("invalid pm_type %d", pmap->pm_type));

	/*
	 * XWR = 010 or 110 will cause an unconditional EPT misconfiguration
	 * so we don't let the referenced (aka EPT_PG_READ) bit to be cleared
	 * if the EPT_PG_WRITE bit is set.
	 */
	if ((pte & EPT_PG_WRITE) != 0)
		return (FALSE);

	/*
	 * XWR = 100 is allowed only if the PMAP_SUPPORTS_EXEC_ONLY is set.
	 */
	if ((pte & EPT_PG_EXECUTE) == 0 ||
	    ((pmap->pm_flags & PMAP_SUPPORTS_EXEC_ONLY) != 0))
		return (TRUE);
	else
		return (FALSE);
}