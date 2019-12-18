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
typedef  TYPE_2__* db_watchpoint_t ;
struct TYPE_5__ {int /*<<< orphan*/  hiaddr; int /*<<< orphan*/  loaddr; TYPE_1__* map; struct TYPE_5__* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PROT_READ ; 
 TYPE_2__* db_watchpoint_list ; 
 int db_watchpoints_inserted ; 
 int /*<<< orphan*/  pmap_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 

void
db_set_watchpoints(void)
{
	db_watchpoint_t	watch;

	if (!db_watchpoints_inserted) {
	    for (watch = db_watchpoint_list;
	         watch != 0;
	         watch = watch->link)
		pmap_protect(watch->map->pmap,
			     trunc_page(watch->loaddr),
			     round_page(watch->hiaddr),
			     VM_PROT_READ);

	    db_watchpoints_inserted = true;
	}
}