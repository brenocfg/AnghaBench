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
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 int /*<<< orphan*/  pmap_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove_l2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spglist*,struct rwlock**) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

__attribute__((used)) static void
pmap_demote_l2_abort(pmap_t pmap, vm_offset_t va, pt_entry_t *l2,
    struct rwlock **lockp)
{
	struct spglist free;

	SLIST_INIT(&free);
	(void)pmap_remove_l2(pmap, l2, va, pmap_load(pmap_l1(pmap, va)), &free,
	    lockp);
	vm_page_free_pages_toq(&free, true);
}