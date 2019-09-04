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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  dbg; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_debug_breakpoint ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_ERR_MSG_NOBPNO_INFOALL ; 
 int /*<<< orphan*/  BREAK_INFO_MSG_HEADER ; 
 int MRB_DEBUG_OK ; 
 int mrb_debug_get_break_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mrb_debug_get_breaknum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_api_common_error (int) ; 
 int /*<<< orphan*/  print_breakpoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
info_break_all(mrb_state *mrb, mrdb_state *mrdb)
{
  int32_t bpnum = 0;
  int32_t i = 0;
  int32_t ret = MRB_DEBUG_OK;
  mrb_debug_breakpoint *bp_list;

  bpnum = mrb_debug_get_breaknum(mrb, mrdb->dbg);
  if (bpnum < 0) {
    print_api_common_error(bpnum);
    return;
  }
  else if (bpnum == 0) {
    puts(BREAK_ERR_MSG_NOBPNO_INFOALL);
    return;
  }
  bp_list = (mrb_debug_breakpoint*)mrb_malloc(mrb, bpnum * sizeof(mrb_debug_breakpoint));

  ret = mrb_debug_get_break_all(mrb, mrdb->dbg, (uint32_t)bpnum, bp_list);
  if (ret < 0) {
    print_api_common_error(ret);
    return;
  }
  puts(BREAK_INFO_MSG_HEADER);
  for(i = 0 ; i < bpnum ; i++) {
    print_breakpoint(&bp_list[i]);
  }

  mrb_free(mrb, bp_list);
}