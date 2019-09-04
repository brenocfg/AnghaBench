#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct loopinfo {int /*<<< orphan*/  pc2; } ;
struct TYPE_28__ {TYPE_2__* cdr; struct TYPE_28__* car; } ;
typedef  TYPE_4__ node ;
struct TYPE_29__ {int /*<<< orphan*/  mrb; TYPE_3__* irep; } ;
typedef  TYPE_5__ codegen_scope ;
struct TYPE_27__ {scalar_t__ rlen; } ;
struct TYPE_26__ {TYPE_1__* cdr; int /*<<< orphan*/  car; } ;
struct TYPE_25__ {int /*<<< orphan*/  car; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOOP_FOR ; 
 int /*<<< orphan*/  NOVAL ; 
 int /*<<< orphan*/  OP_BLOCK ; 
 int /*<<< orphan*/  OP_ENTER ; 
 int /*<<< orphan*/  OP_RETURN ; 
 int /*<<< orphan*/  OP_SENDB ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  codegen (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursp () ; 
 int /*<<< orphan*/  gen_assignment (TYPE_5__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_return (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_vmassignment (TYPE_5__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  genop_3 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_W (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  loop_pop (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct loopinfo* loop_push (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  new_label (TYPE_5__*) ; 
 int new_sym (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  push () ; 
 int /*<<< orphan*/  raise_error (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  scope_finish (TYPE_5__*) ; 
 TYPE_5__* scope_new (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
for_body(codegen_scope *s, node *tree)
{
  codegen_scope *prev = s;
  int idx;
  struct loopinfo *lp;
  node *n2;

  /* generate receiver */
  codegen(s, tree->cdr->car, VAL);
  /* generate loop-block */
  s = scope_new(s->mrb, s, NULL);
  if (s == NULL) {
    raise_error(prev, "unexpected scope");
  }

  push();                       /* push for a block parameter */

  /* generate loop variable */
  n2 = tree->car;
  genop_W(s, OP_ENTER, 0x40000);
  if (n2->car && !n2->car->cdr && !n2->cdr) {
    gen_assignment(s, n2->car->car, 1, NOVAL);
  }
  else {
    gen_vmassignment(s, n2, 1, VAL);
  }
  /* construct loop */
  lp = loop_push(s, LOOP_FOR);
  lp->pc2 = new_label(s);

  /* loop body */
  codegen(s, tree->cdr->cdr->car, VAL);
  pop();
  gen_return(s, OP_RETURN, cursp());
  loop_pop(s, NOVAL);
  scope_finish(s);
  s = prev;
  genop_2(s, OP_BLOCK, cursp(), s->irep->rlen-1);
  push();pop(); /* space for a block */
  pop();
  idx = new_sym(s, mrb_intern_lit(s->mrb, "each"));
  genop_3(s, OP_SENDB, cursp(), idx, 0);
}