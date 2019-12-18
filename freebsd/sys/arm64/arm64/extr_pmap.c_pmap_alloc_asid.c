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
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int /*<<< orphan*/  pm_cookie; } ;

/* Variables and functions */
 int ASID_FIRST_AVAILABLE ; 
 int /*<<< orphan*/  COOKIE_FROM (int,scalar_t__) ; 
 scalar_t__ COOKIE_TO_EPOCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ asid_epoch ; 
 int asid_next ; 
 int /*<<< orphan*/  asid_set ; 
 int /*<<< orphan*/  asid_set_mutex ; 
 int asid_set_size ; 
 int /*<<< orphan*/  bit_ffc_at (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_reset_asid_set () ; 

__attribute__((used)) static void
pmap_alloc_asid(pmap_t pmap)
{
	int new_asid;

	mtx_lock_spin(&asid_set_mutex);

	/*
	 * While this processor was waiting to acquire the asid set mutex,
	 * pmap_reset_asid_set() running on another processor might have
	 * updated this pmap's cookie to the current epoch.  In which case, we
	 * don't need to allocate a new ASID.
	 */
	if (COOKIE_TO_EPOCH(pmap->pm_cookie) == asid_epoch)
		goto out;

	bit_ffc_at(asid_set, asid_next, asid_set_size, &new_asid);
	if (new_asid == -1) {
		bit_ffc_at(asid_set, ASID_FIRST_AVAILABLE, asid_next,
		    &new_asid);
		if (new_asid == -1) {
			pmap_reset_asid_set();
			bit_ffc_at(asid_set, ASID_FIRST_AVAILABLE,
			    asid_set_size, &new_asid);
			KASSERT(new_asid != -1, ("ASID allocation failure"));
		}
	}
	bit_set(asid_set, new_asid);
	asid_next = new_asid + 1;
	pmap->pm_cookie = COOKIE_FROM(new_asid, asid_epoch);
out:
	mtx_unlock_spin(&asid_set_mutex);
}