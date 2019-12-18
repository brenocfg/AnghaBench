#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
struct spglist {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss; } ;
struct TYPE_4__ {TYPE_1__ s; } ;

/* Variables and functions */
 scalar_t__ SLIST_EMPTY (struct spglist*) ; 
 int /*<<< orphan*/ * SLIST_FIRST (struct spglist*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct spglist*,int /*<<< orphan*/ ) ; 
 TYPE_2__ plinks ; 
 int /*<<< orphan*/  vm_page_free_toq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_wire_sub (int) ; 

void
vm_page_free_pages_toq(struct spglist *free, bool update_wire_count)
{
	vm_page_t m;
	int count;

	if (SLIST_EMPTY(free))
		return;

	count = 0;
	while ((m = SLIST_FIRST(free)) != NULL) {
		count++;
		SLIST_REMOVE_HEAD(free, plinks.s.ss);
		vm_page_free_toq(m);
	}

	if (update_wire_count)
		vm_wire_sub(count);
}