#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_6__ {scalar_t__ object; int pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (scalar_t__) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pglist ; 

vm_page_t
vm_page_prev(vm_page_t m)
{
	vm_page_t prev;

	VM_OBJECT_ASSERT_LOCKED(m->object);
	if ((prev = TAILQ_PREV(m, pglist, listq)) != NULL) {
		MPASS(prev->object == m->object);
		if (prev->pindex != m->pindex - 1)
			prev = NULL;
	}
	return (prev);
}