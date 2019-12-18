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
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_demote_pde_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 

__attribute__((used)) static boolean_t
pmap_demote_pde(pmap_t pmap, pd_entry_t *pde, vm_offset_t va)
{
	struct rwlock *lock;
	boolean_t rv;

	lock = NULL;
	rv = pmap_demote_pde_locked(pmap, pde, va, &lock);
	if (lock != NULL)
		rw_wunlock(lock);
	return (rv);
}