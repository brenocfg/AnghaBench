#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct TYPE_4__ {int pv_flags; int /*<<< orphan*/  pv_list; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 int PV_MEMATTR_SHIFT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int VM_MEMATTR_DEFAULT ; 

void
pmap_page_init(vm_page_t m)
{

	TAILQ_INIT(&m->md.pv_list);
	m->md.pv_flags = VM_MEMATTR_DEFAULT << PV_MEMATTR_SHIFT;
}