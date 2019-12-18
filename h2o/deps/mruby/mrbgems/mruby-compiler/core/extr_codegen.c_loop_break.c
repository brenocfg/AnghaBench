#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct loopinfo {scalar_t__ type; scalar_t__ ensure_level; int pc3; int /*<<< orphan*/  acc; struct loopinfo* prev; } ;
typedef  int /*<<< orphan*/  node ;
struct TYPE_10__ {scalar_t__ ensure_level; struct loopinfo* loop; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 scalar_t__ LOOP_BEGIN ; 
 scalar_t__ LOOP_NORMAL ; 
 scalar_t__ LOOP_RESCUE ; 
 int /*<<< orphan*/  NOVAL ; 
 int /*<<< orphan*/  OP_BREAK ; 
 int /*<<< orphan*/  OP_EPOP ; 
 int /*<<< orphan*/  OP_JMP ; 
 int /*<<< orphan*/  OP_LOADNIL ; 
 int /*<<< orphan*/  OP_POPERR ; 
 int /*<<< orphan*/  codegen (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cursp () ; 
 int /*<<< orphan*/  gen_move (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_return (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_retval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int genjmp (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genop_1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raise_error (TYPE_1__*,char*) ; 

__attribute__((used)) static void
loop_break(codegen_scope *s, node *tree)
{
  if (!s->loop) {
    codegen(s, tree, NOVAL);
    raise_error(s, "unexpected break");
  }
  else {
    struct loopinfo *loop;
    int n = 0;

    if (tree) {
      gen_retval(s, tree);
    }

    loop = s->loop;
    while (loop) {
      if (loop->type == LOOP_BEGIN) {
        n++;
        loop = loop->prev;
      }
      else if (loop->type == LOOP_RESCUE) {
        loop = loop->prev;
      }
      else{
        break;
      }
    }
    if (!loop) {
      raise_error(s, "unexpected break");
      return;
    }
    if (n > 0) {
      genop_1(s, OP_POPERR, n);
    }

    if (loop->type == LOOP_NORMAL) {
      int tmp;

      if (s->ensure_level > s->loop->ensure_level) {
        genop_1(s, OP_EPOP, s->ensure_level - s->loop->ensure_level);
      }
      if (tree) {
        gen_move(s, loop->acc, cursp(), 0);
      }
      tmp = genjmp(s, OP_JMP, loop->pc3);
      loop->pc3 = tmp;
    }
    else {
      if (!tree) {
        genop_1(s, OP_LOADNIL, cursp());
      }
      gen_return(s, OP_BREAK, cursp());
    }
  }
}