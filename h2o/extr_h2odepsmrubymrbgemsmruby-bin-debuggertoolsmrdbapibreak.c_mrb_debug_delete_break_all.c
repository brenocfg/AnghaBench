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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {size_t bpnum; int /*<<< orphan*/ * bp; } ;
typedef  TYPE_1__ mrb_debug_context ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_DEBUG_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  MRB_DEBUG_OK ; 
 int /*<<< orphan*/  free_breakpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t
mrb_debug_delete_break_all(mrb_state *mrb, mrb_debug_context *dbg)
{
  uint32_t i;

  if ((mrb == NULL) || (dbg == NULL)) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  for(i = 0 ; i < dbg->bpnum ; i++) {
    free_breakpoint(mrb, &dbg->bp[i]);
  }

  dbg->bpnum = 0;

  return MRB_DEBUG_OK;
}