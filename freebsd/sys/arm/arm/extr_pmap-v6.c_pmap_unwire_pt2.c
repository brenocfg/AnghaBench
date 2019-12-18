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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (int /*<<< orphan*/ ,struct spglist*) ; 
 int /*<<< orphan*/  pmap_unwire_pt2pg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt2_wirecount_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pt2pg_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline boolean_t
pmap_unwire_pt2(pmap_t pmap, vm_offset_t va, vm_page_t m, struct spglist *free)
{
	pt2_wirecount_dec(m, pte1_index(va));
	if (pt2pg_is_empty(m)) {
		/*
		 * QQQ: Wire count is zero, so whole page should be zero and
		 *      we can set PG_ZERO flag to it.
		 *      Note that when promotion is enabled, it takes some
		 *      more efforts. See pmap_unwire_pt2_all() below.
		 */
		pmap_unwire_pt2pg(pmap, va, m);
		pmap_add_delayed_free_list(m, free);
		return (TRUE);
	} else
		return (FALSE);
}