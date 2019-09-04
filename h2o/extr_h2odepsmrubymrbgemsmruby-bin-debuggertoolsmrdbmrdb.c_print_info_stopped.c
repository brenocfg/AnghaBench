#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* dbg; } ;
typedef  TYPE_2__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {int bm; } ;

/* Variables and functions */
#define  BRK_BREAK 130 
#define  BRK_NEXT 129 
#define  BRK_STEP 128 
 int /*<<< orphan*/  print_info_stopped_break (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  print_info_stopped_code (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  print_info_stopped_step_next (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
print_info_stopped(mrb_state *mrb, mrdb_state *mrdb)
{
  switch(mrdb->dbg->bm) {
    case BRK_BREAK:
      print_info_stopped_break(mrb, mrdb);
      print_info_stopped_code(mrb, mrdb);
      break;
    case BRK_STEP:
    case BRK_NEXT:
      print_info_stopped_step_next(mrb, mrdb);
      print_info_stopped_code(mrb, mrdb);
      break;
    default:
      break;
  }
}