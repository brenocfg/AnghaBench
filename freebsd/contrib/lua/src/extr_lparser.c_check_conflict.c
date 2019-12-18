#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ vt; int t; int idx; } ;
struct TYPE_13__ {TYPE_1__ ind; } ;
struct TYPE_14__ {scalar_t__ k; TYPE_2__ u; } ;
struct LHS_assign {TYPE_3__ v; struct LHS_assign* prev; } ;
struct TYPE_15__ {int info; } ;
struct TYPE_16__ {scalar_t__ k; TYPE_4__ u; } ;
typedef  TYPE_5__ expdesc ;
struct TYPE_18__ {int freereg; } ;
struct TYPE_17__ {TYPE_7__* fs; } ;
typedef  int /*<<< orphan*/  OpCode ;
typedef  TYPE_6__ LexState ;
typedef  TYPE_7__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_GETUPVAL ; 
 int /*<<< orphan*/  OP_MOVE ; 
 scalar_t__ VINDEXED ; 
 scalar_t__ VLOCAL ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_7__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_7__*,int) ; 

__attribute__((used)) static void check_conflict (LexState *ls, struct LHS_assign *lh, expdesc *v) {
  FuncState *fs = ls->fs;
  int extra = fs->freereg;  /* eventual position to save local variable */
  int conflict = 0;
  for (; lh; lh = lh->prev) {  /* check all previous assignments */
    if (lh->v.k == VINDEXED) {  /* assigning to a table? */
      /* table is the upvalue/local being assigned now? */
      if (lh->v.u.ind.vt == v->k && lh->v.u.ind.t == v->u.info) {
        conflict = 1;
        lh->v.u.ind.vt = VLOCAL;
        lh->v.u.ind.t = extra;  /* previous assignment will use safe copy */
      }
      /* index is the local being assigned? (index cannot be upvalue) */
      if (v->k == VLOCAL && lh->v.u.ind.idx == v->u.info) {
        conflict = 1;
        lh->v.u.ind.idx = extra;  /* previous assignment will use safe copy */
      }
    }
  }
  if (conflict) {
    /* copy upvalue/local value to a temporary (in position 'extra') */
    OpCode op = (v->k == VLOCAL) ? OP_MOVE : OP_GETUPVAL;
    luaK_codeABC(fs, op, extra, v->u.info, 0);
    luaK_reserveregs(fs, 1);
  }
}