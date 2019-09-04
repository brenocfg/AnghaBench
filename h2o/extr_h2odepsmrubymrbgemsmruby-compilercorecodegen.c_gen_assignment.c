#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* car; struct TYPE_21__* cdr; } ;
typedef  TYPE_1__ node ;
struct TYPE_22__ {struct TYPE_22__* prev; } ;
typedef  TYPE_2__ codegen_scope ;

/* Variables and functions */
#define  NODE_ARG 138 
#define  NODE_CALL 137 
#define  NODE_COLON2 136 
#define  NODE_CONST 135 
#define  NODE_CVAR 134 
#define  NODE_GVAR 133 
#define  NODE_IVAR 132 
#define  NODE_LVAR 131 
#define  NODE_MASGN 130 
#define  NODE_NIL 129 
#define  NODE_SCALL 128 
 int /*<<< orphan*/  NOVAL ; 
 int /*<<< orphan*/  OP_NOP ; 
 int /*<<< orphan*/  OP_SETCONST ; 
 int /*<<< orphan*/  OP_SETCV ; 
 int /*<<< orphan*/  OP_SETGV ; 
 int /*<<< orphan*/  OP_SETIV ; 
 int /*<<< orphan*/  OP_SETMCNST ; 
 int /*<<< orphan*/  OP_SETUPVAR ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  attrsym (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int cursp () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gen_call (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_move (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  gen_vmassignment (TYPE_2__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  genop_0 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  genop_3 (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int lv_idx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int new_sym (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int nint (TYPE_1__*) ; 
 int /*<<< orphan*/  nsym (TYPE_1__*) ; 
 int /*<<< orphan*/  on_eval (TYPE_2__*) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  pop_n (int) ; 
 int /*<<< orphan*/  push () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
gen_assignment(codegen_scope *s, node *tree, int sp, int val)
{
  int idx;
  int type = nint(tree->car);

  tree = tree->cdr;
  switch (type) {
  case NODE_GVAR:
    idx = new_sym(s, nsym(tree));
    genop_2(s, OP_SETGV, sp, idx);
    break;
  case NODE_ARG:
  case NODE_LVAR:
    idx = lv_idx(s, nsym(tree));
    if (idx > 0) {
      if (idx != sp) {
        gen_move(s, idx, sp, val);
        if (val && on_eval(s)) genop_0(s, OP_NOP);
      }
      break;
    }
    else {                      /* upvar */
      int lv = 0;
      codegen_scope *up = s->prev;

      while (up) {
        idx = lv_idx(up, nsym(tree));
        if (idx > 0) {
          genop_3(s, OP_SETUPVAR, sp, idx, lv);
          break;
        }
        lv++;
        up = up->prev;
      }
    }
    break;
  case NODE_IVAR:
    idx = new_sym(s, nsym(tree));
    genop_2(s, OP_SETIV, sp, idx);
    break;
  case NODE_CVAR:
    idx = new_sym(s, nsym(tree));
    genop_2(s, OP_SETCV, sp, idx);
    break;
  case NODE_CONST:
    idx = new_sym(s, nsym(tree));
    genop_2(s, OP_SETCONST, sp, idx);
    break;
  case NODE_COLON2:
    gen_move(s, cursp(), sp, 0);
    push();
    codegen(s, tree->car, VAL);
    pop_n(2);
    idx = new_sym(s, nsym(tree->cdr));
    genop_2(s, OP_SETMCNST, sp, idx);
    break;

  case NODE_CALL:
  case NODE_SCALL:
    push();
    gen_call(s, tree, attrsym(s, nsym(tree->cdr->car)), sp, NOVAL,
             type == NODE_SCALL);
    pop();
    if (val) {
      gen_move(s, cursp(), sp, 0);
    }
    break;

  case NODE_MASGN:
    gen_vmassignment(s, tree->car, sp, val);
    break;

  /* splat without assignment */
  case NODE_NIL:
    break;

  default:
#ifndef MRB_DISABLE_STDIO
    fprintf(stderr, "unknown lhs %d\n", type);
#endif
    break;
  }
  if (val) push();
}