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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct TYPE_4__ {int segind; scalar_t__ dirty; scalar_t__ valid; int /*<<< orphan*/  pool; int /*<<< orphan*/  order; scalar_t__ psind; int /*<<< orphan*/  queue; int /*<<< orphan*/  phys_addr; scalar_t__ aflags; scalar_t__ flags; int /*<<< orphan*/  busy_lock; scalar_t__ ref_count; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_NONE ; 
 int /*<<< orphan*/  VM_FREEPOOL_DEFAULT ; 
 int /*<<< orphan*/  VM_NFREEORDER ; 
 int /*<<< orphan*/  VPB_UNBUSIED ; 
 int /*<<< orphan*/  pmap_page_init (TYPE_1__*) ; 

__attribute__((used)) static void
vm_page_init_page(vm_page_t m, vm_paddr_t pa, int segind)
{

	m->object = NULL;
	m->ref_count = 0;
	m->busy_lock = VPB_UNBUSIED;
	m->flags = m->aflags = 0;
	m->phys_addr = pa;
	m->queue = PQ_NONE;
	m->psind = 0;
	m->segind = segind;
	m->order = VM_NFREEORDER;
	m->pool = VM_FREEPOOL_DEFAULT;
	m->valid = m->dirty = 0;
	pmap_page_init(m);
}