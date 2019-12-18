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
typedef  TYPE_1__* vm_page_t ;
struct vm_freelist {int /*<<< orphan*/  lcnt; int /*<<< orphan*/  pl; } ;
struct TYPE_4__ {int /*<<< orphan*/  order; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_NFREEORDER ; 
 int /*<<< orphan*/  listq ; 

__attribute__((used)) static void
vm_freelist_rem(struct vm_freelist *fl, vm_page_t m, int order)
{

	TAILQ_REMOVE(&fl[order].pl, m, listq);
	fl[order].lcnt--;
	m->order = VM_NFREEORDER;
}