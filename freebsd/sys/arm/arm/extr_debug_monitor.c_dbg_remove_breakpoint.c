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
typedef  int /*<<< orphan*/  u_int ;
struct dbg_wb_conf {int /*<<< orphan*/  type; int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TYPE_BREAKPOINT ; 
 scalar_t__ dbg_check_slot_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbg_remove_xpoint (struct dbg_wb_conf*) ; 

__attribute__((used)) static int
dbg_remove_breakpoint(u_int slot)
{
	struct dbg_wb_conf conf;

	/* Slot already cleared. Don't recurse */
	if (dbg_check_slot_free(DBG_TYPE_BREAKPOINT, slot))
		return (0);

	conf.slot = slot;
	conf.type = DBG_TYPE_BREAKPOINT;

	return (dbg_remove_xpoint(&conf));
}