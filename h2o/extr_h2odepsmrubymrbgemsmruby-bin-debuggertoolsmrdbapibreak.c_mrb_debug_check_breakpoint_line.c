#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {scalar_t__ lineno; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ mrb_debug_linepoint ;
struct TYPE_8__ {scalar_t__ bpnum; TYPE_4__* bp; int /*<<< orphan*/  pc; int /*<<< orphan*/  irep; } ;
typedef  TYPE_3__ mrb_debug_context ;
struct TYPE_6__ {TYPE_2__ linepoint; } ;
struct TYPE_9__ {int type; int /*<<< orphan*/  bpno; TYPE_1__ point; int /*<<< orphan*/  enable; } ;
typedef  TYPE_4__ mrb_debug_breakpoint ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  MRB_DEBUG_BPTYPE_LINE 130 
#define  MRB_DEBUG_BPTYPE_METHOD 129 
#define  MRB_DEBUG_BPTYPE_NONE 128 
 int /*<<< orphan*/  MRB_DEBUG_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  MRB_DEBUG_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_start_pc_for_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int32_t
mrb_debug_check_breakpoint_line(mrb_state *mrb, mrb_debug_context *dbg, const char *file, uint16_t line)
{
  mrb_debug_breakpoint *bp;
  mrb_debug_linepoint *line_p;
  uint32_t i;

  if ((mrb == NULL) || (dbg == NULL) || (file == NULL) || (line <= 0)) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  if (!check_start_pc_for_line(dbg->irep, dbg->pc, line)) {
    return MRB_DEBUG_OK;
  }

  bp = dbg->bp;
  for(i=0; i<dbg->bpnum; i++) {
    switch (bp->type) {
      case MRB_DEBUG_BPTYPE_LINE:
        if (bp->enable == TRUE) {
          line_p = &bp->point.linepoint;
          if ((strcmp(line_p->file, file) == 0) && (line_p->lineno == line)) {
            return bp->bpno;
          }
        }
        break;
      case MRB_DEBUG_BPTYPE_METHOD:
        break;
      case MRB_DEBUG_BPTYPE_NONE:
      default:
        return MRB_DEBUG_OK;
    }
    bp++;
  }
  return MRB_DEBUG_OK;
}