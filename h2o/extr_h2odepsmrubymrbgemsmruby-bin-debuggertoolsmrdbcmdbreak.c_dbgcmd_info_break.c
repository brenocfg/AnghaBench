#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int wcnt; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_PROMPT ; 
 int /*<<< orphan*/  info_break_all (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  info_break_select (int /*<<< orphan*/ *,TYPE_1__*) ; 

dbgcmd_state
dbgcmd_info_break(mrb_state *mrb, mrdb_state *mrdb)
{
  if (mrdb->wcnt == 2) {
    info_break_all(mrb, mrdb);
  }
  else {
    info_break_select(mrb, mrdb);
  }

  return DBGST_PROMPT;
}