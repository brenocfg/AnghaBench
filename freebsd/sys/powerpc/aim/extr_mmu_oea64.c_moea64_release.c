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
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_4__ {scalar_t__* pm_sr; int /*<<< orphan*/  pm_slb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VSID_TO_HASH (scalar_t__) ; 
 int /*<<< orphan*/  moea64_release_vsid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slb_free_tree (TYPE_1__*) ; 
 int /*<<< orphan*/  slb_free_user_cache (int /*<<< orphan*/ ) ; 

void
moea64_release(mmu_t mmu, pmap_t pmap)
{
        
	/*
	 * Free segment registers' VSIDs
	 */
    #ifdef __powerpc64__
	slb_free_tree(pmap);
	slb_free_user_cache(pmap->pm_slb);
    #else
	KASSERT(pmap->pm_sr[0] != 0, ("moea64_release: pm_sr[0] = 0"));

	moea64_release_vsid(VSID_TO_HASH(pmap->pm_sr[0]));
    #endif
}