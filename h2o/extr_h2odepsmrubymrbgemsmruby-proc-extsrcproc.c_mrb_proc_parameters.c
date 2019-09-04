#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mrb_irep {scalar_t__* iseq; int nlocals; TYPE_2__* lv; } ;
struct TYPE_3__ {struct mrb_irep* irep; } ;
struct RProc {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_aspec ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MRB_ASPEC_BLOCK (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_OPT (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_POST (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_REQ (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_REST (int /*<<< orphan*/ ) ; 
 scalar_t__ MRB_PROC_CFUNC_P (struct RProc const*) ; 
 int /*<<< orphan*/  MRB_PROC_STRICT_P (struct RProc const*) ; 
 scalar_t__ OP_ENTER ; 
 int /*<<< orphan*/  PEEK_W (scalar_t__*) ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_static (int /*<<< orphan*/ *,char*,int) ; 
 struct RProc* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 char* mrb_sym2name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_proc_parameters(mrb_state *mrb, mrb_value self)
{
  struct parameters_type {
    size_t len;
    const char *name;
    int size;
  } *p, parameters_list [] = {
    {sizeof("req")   - 1, "req",   0},
    {sizeof("opt")   - 1, "opt",   0},
    {sizeof("rest")  - 1, "rest",  0},
    {sizeof("req")   - 1, "req",   0},
    {sizeof("block") - 1, "block", 0},
    {0, NULL, 0}
  };
  const struct RProc *proc = mrb_proc_ptr(self);
  const struct mrb_irep *irep = proc->body.irep;
  mrb_aspec aspec;
  mrb_value parameters;
  int i, j;
  int max = -1;

  if (MRB_PROC_CFUNC_P(proc)) {
    // TODO cfunc aspec is not implemented yet
    return mrb_ary_new(mrb);
  }
  if (!irep) {
    return mrb_ary_new(mrb);
  }
  if (!irep->lv) {
    return mrb_ary_new(mrb);
  }
  if (*irep->iseq != OP_ENTER) {
    return mrb_ary_new(mrb);
  }

  if (!MRB_PROC_STRICT_P(proc)) {
    parameters_list[0].len = sizeof("opt") - 1;
    parameters_list[0].name = "opt";
    parameters_list[3].len = sizeof("opt") - 1;
    parameters_list[3].name = "opt";
  }

  aspec = PEEK_W(irep->iseq+1);
  parameters_list[0].size = MRB_ASPEC_REQ(aspec);
  parameters_list[1].size = MRB_ASPEC_OPT(aspec);
  parameters_list[2].size = MRB_ASPEC_REST(aspec);
  parameters_list[3].size = MRB_ASPEC_POST(aspec);
  parameters_list[4].size = MRB_ASPEC_BLOCK(aspec);

  parameters = mrb_ary_new_capa(mrb, irep->nlocals-1);

  max = irep->nlocals-1;
  for (i = 0, p = parameters_list; p->name; p++) {
    mrb_value sname = mrb_symbol_value(mrb_intern_static(mrb, p->name, p->len));

    for (j = 0; j < p->size; i++, j++) {
      mrb_value a;

      a = mrb_ary_new(mrb);
      mrb_ary_push(mrb, a, sname);
      if (i < max && irep->lv[i].name) {
        mrb_sym sym = irep->lv[i].name;
        const char *name = mrb_sym2name(mrb, sym);
        switch (name[0]) {
        case '*': case '&':
          break;
        default:
          mrb_ary_push(mrb, a, mrb_symbol_value(sym));
          break;
        }
      }
      mrb_ary_push(mrb, parameters, a);
    }
  }
  return parameters;
}