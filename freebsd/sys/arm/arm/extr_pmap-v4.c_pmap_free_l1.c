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
struct l1_ttable {scalar_t__ l1_domain_use_count; int* l1_domain_free; int l1_domain_first; } ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int pm_domain; struct l1_ttable* pm_l1; } ;

/* Variables and functions */
 scalar_t__ PMAP_DOMAINS ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct l1_ttable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct l1_ttable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct l1_ttable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l1_lru ; 
 int /*<<< orphan*/  l1_lru_list ; 
 int /*<<< orphan*/  l1_lru_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmap_free_l1(pmap_t pm)
{
	struct l1_ttable *l1 = pm->pm_l1;

	mtx_lock(&l1_lru_lock);

	/*
	 * If this L1 is currently on the LRU list, remove it.
	 */
	if (l1->l1_domain_use_count < PMAP_DOMAINS)
		TAILQ_REMOVE(&l1_lru_list, l1, l1_lru);

	/*
	 * Free up the domain number which was allocated to the pmap
	 */
	l1->l1_domain_free[pm->pm_domain - 1] = l1->l1_domain_first;
	l1->l1_domain_first = pm->pm_domain - 1;
	l1->l1_domain_use_count--;

	/*
	 * The L1 now must have at least 1 free domain, so add
	 * it back to the LRU list. If the use count is zero,
	 * put it at the head of the list, otherwise it goes
	 * to the tail.
	 */
	if (l1->l1_domain_use_count == 0) {
		TAILQ_INSERT_HEAD(&l1_lru_list, l1, l1_lru);
	}	else
		TAILQ_INSERT_TAIL(&l1_lru_list, l1, l1_lru);

	mtx_unlock(&l1_lru_lock);
}