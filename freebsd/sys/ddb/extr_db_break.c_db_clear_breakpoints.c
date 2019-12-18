#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* db_breakpoint_t ;
struct TYPE_3__ {int /*<<< orphan*/  bkpt_inst; int /*<<< orphan*/  address; int /*<<< orphan*/  map; struct TYPE_3__* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  BKPT_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* db_breakpoint_list ; 
 int db_breakpoints_inserted ; 
 scalar_t__ db_map_current (int /*<<< orphan*/ ) ; 

void
db_clear_breakpoints(void)
{
	register db_breakpoint_t	bkpt;

	if (db_breakpoints_inserted) {

		for (bkpt = db_breakpoint_list;
		     bkpt != 0;
		     bkpt = bkpt->link)
			if (db_map_current(bkpt->map)) {
				BKPT_CLEAR(bkpt->address, &bkpt->bkpt_inst);
			}
		db_breakpoints_inserted = false;
	}
}