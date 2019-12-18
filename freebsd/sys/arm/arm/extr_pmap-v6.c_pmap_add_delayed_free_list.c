#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct spglist {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ss; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_ZERO ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct spglist*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ plinks ; 
 int /*<<< orphan*/  pmap_zero_page_check (TYPE_2__*) ; 

__attribute__((used)) static __inline void
pmap_add_delayed_free_list(vm_page_t m, struct spglist *free)
{

	/*
	 * Put page on a list so that it is released after
	 * *ALL* TLB shootdown is done
	 */
#ifdef PMAP_DEBUG
	pmap_zero_page_check(m);
#endif
	m->flags |= PG_ZERO;
	SLIST_INSERT_HEAD(free, m, plinks.s.ss);
}