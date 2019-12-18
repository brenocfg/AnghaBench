#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int info; } ;
struct TYPE_7__ {scalar_t__ k; TYPE_1__ u; void* t; void* f; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 void* NO_JUMP ; 
 scalar_t__ VJMP ; 
 scalar_t__ VNONRELOC ; 
 int code_label (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  discharge2reg (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ hasjumps (TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,void**,int) ; 
 int luaK_getlabel (int /*<<< orphan*/ *) ; 
 void* luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 scalar_t__ need_value (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  patchlistaux (int /*<<< orphan*/ *,void*,int,int,int) ; 

__attribute__((used)) static void exp2reg (FuncState *fs, expdesc *e, int reg) {
  discharge2reg(fs, e, reg);
  if (e->k == VJMP)
    luaK_concat(fs, &e->t, e->u.info);  /* put this jump in `t' list */
  if (hasjumps(e)) {
    int final;  /* position after whole expression */
    int p_f = NO_JUMP;  /* position of an eventual LOAD false */
    int p_t = NO_JUMP;  /* position of an eventual LOAD true */
    if (need_value(fs, e->t) || need_value(fs, e->f)) {
      int fj = (e->k == VJMP) ? NO_JUMP : luaK_jump(fs);
      p_f = code_label(fs, reg, 0, 1);
      p_t = code_label(fs, reg, 1, 0);
      luaK_patchtohere(fs, fj);
    }
    final = luaK_getlabel(fs);
    patchlistaux(fs, e->f, final, reg, p_f);
    patchlistaux(fs, e->t, final, reg, p_t);
  }
  e->f = e->t = NO_JUMP;
  e->u.info = reg;
  e->k = VNONRELOC;
}