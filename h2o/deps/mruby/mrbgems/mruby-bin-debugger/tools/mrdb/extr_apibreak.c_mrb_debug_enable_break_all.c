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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {size_t bpnum; TYPE_1__* bp; } ;
typedef  TYPE_2__ mrb_debug_context ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_DEBUG_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  MRB_DEBUG_OK ; 
 int /*<<< orphan*/  TRUE ; 

int32_t
mrb_debug_enable_break_all(mrb_state *mrb, mrb_debug_context *dbg)
{
  uint32_t i;

  if ((mrb == NULL) || (dbg == NULL)) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  for(i = 0 ; i < dbg->bpnum; i++) {
    dbg->bp[i].enable = TRUE;
  }

  return MRB_DEBUG_OK;
}