#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_19__ {TYPE_1__* c; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_20__ {int iseq; } ;
typedef  TYPE_3__ mrb_irep ;
struct TYPE_21__ {scalar_t__ xphase; char const* prvfile; scalar_t__ prvline; int xm; scalar_t__ bm; scalar_t__ ccnt; int /*<<< orphan*/  (* break_hook ) (TYPE_2__*,TYPE_4__*) ;TYPE_3__* root_irep; scalar_t__ stopped_bpno; int /*<<< orphan*/  method_bpno; int /*<<< orphan*/ * prvci; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * pc; TYPE_3__* irep; } ;
typedef  TYPE_4__ mrb_debug_context ;
typedef  int /*<<< orphan*/  mrb_code ;
typedef  scalar_t__ int32_t ;
struct TYPE_18__ {int /*<<< orphan*/  ci; } ;

/* Variables and functions */
 scalar_t__ BRK_BREAK ; 
 scalar_t__ BRK_INIT ; 
 scalar_t__ BRK_NEXT ; 
 scalar_t__ BRK_STEP ; 
#define  DBG_INIT 131 
#define  DBG_NEXT 130 
 scalar_t__ DBG_PHASE_RESTART ; 
 void* DBG_PHASE_RUNNING ; 
#define  DBG_RUN 129 
#define  DBG_STEP 128 
 scalar_t__ check_method_breakpoint (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_assert (TYPE_4__*) ; 
 scalar_t__ mrb_debug_check_breakpoint_line (TYPE_2__*,TYPE_4__*,char const*,scalar_t__) ; 
 TYPE_4__* mrb_debug_context_get (TYPE_2__*) ; 
 char* mrb_debug_get_filename (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_debug_get_line (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static void
mrb_code_fetch_hook(mrb_state *mrb, mrb_irep *irep, mrb_code *pc, mrb_value *regs)
{
  const char *file;
  int32_t line;
  int32_t bpno;

  mrb_debug_context *dbg = mrb_debug_context_get(mrb);

  mrb_assert(dbg);

  dbg->irep = irep;
  dbg->pc   = pc;
  dbg->regs = regs;

  if (dbg->xphase == DBG_PHASE_RESTART) {
    dbg->root_irep = irep;
    dbg->prvfile = NULL;
    dbg->prvline = 0;
    dbg->prvci = NULL;
    dbg->xm = DBG_RUN;
    dbg->xphase = DBG_PHASE_RUNNING;
  }

  file = mrb_debug_get_filename(irep, pc - irep->iseq);
  line = mrb_debug_get_line(irep, pc - irep->iseq);

  switch (dbg->xm) {
  case DBG_STEP:
    if (!file || (dbg->prvfile == file && dbg->prvline == line)) {
      return;
    }
    dbg->method_bpno = 0;
    dbg->bm = BRK_STEP;
    break;

  case DBG_NEXT:
    if (!file || (dbg->prvfile == file && dbg->prvline == line)) {
      return;
    }
    if ((intptr_t)(dbg->prvci) < (intptr_t)(mrb->c->ci)) {
      return;
    }
    dbg->prvci = NULL;
    dbg->method_bpno = 0;
    dbg->bm = BRK_NEXT;
    break;

  case DBG_RUN:
    bpno = check_method_breakpoint(mrb, irep, pc, regs);
    if (bpno > 0) {
      dbg->stopped_bpno = bpno;
      dbg->bm = BRK_BREAK;
      break;
    }
    if (dbg->prvfile != file || dbg->prvline != line) {
      bpno = mrb_debug_check_breakpoint_line(mrb, dbg, file, line);
      if (bpno > 0) {
        dbg->stopped_bpno = bpno;
        dbg->bm = BRK_BREAK;
        break;
      }
    }
    dbg->prvfile = file;
    dbg->prvline = line;
    return;
  case DBG_INIT:
    dbg->root_irep = irep;
    dbg->bm = BRK_INIT;
    if (!file || line < 0) {
      puts("Cannot get debugging information.");
    }
    break;

  default:
    return;
  }

  dbg->prvfile = file;
  dbg->prvline = line;

  if (dbg->bm == BRK_BREAK && --dbg->ccnt > 0) {
    return;
  }
  dbg->break_hook(mrb, dbg);

  dbg->xphase = DBG_PHASE_RUNNING;
}