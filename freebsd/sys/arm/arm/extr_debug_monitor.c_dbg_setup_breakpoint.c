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
struct dbg_wb_conf {int /*<<< orphan*/  slot; int /*<<< orphan*/  type; int /*<<< orphan*/  access; void* size; void* address; } ;
typedef  void* db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TYPE_BREAKPOINT ; 
 int /*<<< orphan*/  HW_BREAKPOINT_X ; 
 int dbg_setup_xpoint (struct dbg_wb_conf*) ; 

__attribute__((used)) static int
dbg_setup_breakpoint(db_expr_t addr, db_expr_t size, u_int slot)
{
	struct dbg_wb_conf conf;

	conf.address = addr;
	conf.size = size;
	conf.access = HW_BREAKPOINT_X;
	conf.type = DBG_TYPE_BREAKPOINT;
	conf.slot = slot;

	return (dbg_setup_xpoint(&conf));
}