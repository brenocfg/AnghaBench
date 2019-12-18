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
struct TYPE_5__ {TYPE_1__* dbg; } ;
typedef  TYPE_2__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;
struct TYPE_4__ {int /*<<< orphan*/  xm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_CONTINUE ; 
 int /*<<< orphan*/  DBG_STEP ; 

dbgcmd_state
dbgcmd_step(mrb_state *mrb, mrdb_state *mrdb)
{
  mrdb->dbg->xm = DBG_STEP;
  return DBGST_CONTINUE;
}