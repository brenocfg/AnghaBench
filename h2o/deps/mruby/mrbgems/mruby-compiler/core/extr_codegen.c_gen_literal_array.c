#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* cdr; TYPE_4__* car; } ;
typedef  TYPE_2__ node ;
typedef  scalar_t__ mrb_bool ;
typedef  int /*<<< orphan*/  codegen_scope ;
struct TYPE_7__ {int /*<<< orphan*/  car; TYPE_1__* cdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdr; } ;

/* Variables and functions */
#define  NODE_BEGIN 131 
#define  NODE_BLOCK 130 
#define  NODE_LITERAL_DELIM 129 
#define  NODE_STR 128 
 int /*<<< orphan*/  NOVAL ; 
 int /*<<< orphan*/  OP_ARRAY ; 
 int /*<<< orphan*/  OP_STRCAT ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursp () ; 
 int /*<<< orphan*/  gen_intern (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genop_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  pop_n (int) ; 
 int /*<<< orphan*/  push () ; 

__attribute__((used)) static void
gen_literal_array(codegen_scope *s, node *tree, mrb_bool sym, int val)
{
  if (val) {
    int i = 0, j = 0;

    while (tree) {
      switch (nint(tree->car->car)) {
      case NODE_STR:
        if ((tree->cdr == NULL) && (nint(tree->car->cdr->cdr) == 0))
          break;
        /* fall through */
      case NODE_BEGIN:
        codegen(s, tree->car, VAL);
        ++j;
        break;

      case NODE_LITERAL_DELIM:
        if (j > 0) {
          j = 0;
          ++i;
          if (sym)
            gen_intern(s);
        }
        break;
      }
      while (j >= 2) {
        pop(); pop();
        genop_1(s, OP_STRCAT, cursp());
        push();
        j--;
      }
      tree = tree->cdr;
    }
    if (j > 0) {
      ++i;
      if (sym)
        gen_intern(s);
    }
    pop_n(i);
    genop_2(s, OP_ARRAY, cursp(), i);
    push();
  }
  else {
    while (tree) {
      switch (nint(tree->car->car)) {
      case NODE_BEGIN: case NODE_BLOCK:
        codegen(s, tree->car, NOVAL);
      }
      tree = tree->cdr;
    }
  }
}