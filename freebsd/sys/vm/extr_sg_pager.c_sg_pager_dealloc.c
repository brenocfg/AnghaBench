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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_3__* vm_object_t ;
struct sglist {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  q; } ;
struct TYPE_6__ {int /*<<< orphan*/  sgp_pglist; } ;
struct TYPE_7__ {TYPE_1__ sgp; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; struct sglist* handle; TYPE_2__ un_pager; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJT_DEAD ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ plinks ; 
 int /*<<< orphan*/  sglist_free (struct sglist*) ; 
 int /*<<< orphan*/  vm_page_putfake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sg_pager_dealloc(vm_object_t object)
{
	struct sglist *sg;
	vm_page_t m;

	/*
	 * Free up our fake pages.
	 */
	while ((m = TAILQ_FIRST(&object->un_pager.sgp.sgp_pglist)) != 0) {
		TAILQ_REMOVE(&object->un_pager.sgp.sgp_pglist, m, plinks.q);
		vm_page_putfake(m);
	}
	
	sg = object->handle;
	sglist_free(sg);
	object->handle = NULL;
	object->type = OBJT_DEAD;
}