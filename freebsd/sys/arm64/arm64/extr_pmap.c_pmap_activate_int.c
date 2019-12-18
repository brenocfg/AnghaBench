#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_8__ {int /*<<< orphan*/  pm_cookie; } ;

/* Variables and functions */
 int COOKIE_TO_EPOCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_1__* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int asid_epoch ; 
 int /*<<< orphan*/  bcast_tlbi_workaround ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_local_icache () ; 
 int /*<<< orphan*/  ish ; 
 TYPE_1__* kernel_pmap ; 
 int /*<<< orphan*/  pmap_alloc_asid (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_to_ttbr0 (TYPE_1__*) ; 
 int /*<<< orphan*/  set_ttbr0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pmap_activate_int(pmap_t pmap)
{
	int epoch;

	KASSERT(PCPU_GET(curpmap) != NULL, ("no active pmap"));
	KASSERT(pmap != kernel_pmap, ("kernel pmap activation"));
	if (pmap == PCPU_GET(curpmap))
		return (false);

	/*
	 * Ensure that the store to curpmap is globally visible before the
	 * load from asid_epoch is performed.
	 */
	PCPU_SET(curpmap, pmap);
	dsb(ish);
	epoch = COOKIE_TO_EPOCH(pmap->pm_cookie);
	if (epoch >= 0 && epoch != asid_epoch)
		pmap_alloc_asid(pmap);

	set_ttbr0(pmap_to_ttbr0(pmap));
	if (PCPU_GET(bcast_tlbi_workaround) != 0)
		invalidate_local_icache();
	return (true);
}