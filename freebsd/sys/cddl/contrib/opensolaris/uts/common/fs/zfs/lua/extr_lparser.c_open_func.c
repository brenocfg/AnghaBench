#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_18__ {int /*<<< orphan*/  h; TYPE_4__* f; int /*<<< orphan*/ * bl; int /*<<< orphan*/  firstlocal; scalar_t__ nactvar; scalar_t__ nlocvars; scalar_t__ nups; scalar_t__ np; scalar_t__ nk; scalar_t__ freereg; int /*<<< orphan*/  jpc; scalar_t__ lasttarget; scalar_t__ pc; TYPE_5__* ls; struct TYPE_18__* prev; } ;
struct TYPE_17__ {int /*<<< orphan*/  source; TYPE_2__* dyd; TYPE_6__* fs; TYPE_3__* L; } ;
struct TYPE_16__ {int maxstacksize; int /*<<< orphan*/  source; } ;
struct TYPE_13__ {int /*<<< orphan*/  n; } ;
struct TYPE_14__ {TYPE_1__ actvar; } ;
typedef  TYPE_4__ Proto ;
typedef  TYPE_5__ LexState ;
typedef  TYPE_6__ FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  NO_JUMP ; 
 int /*<<< orphan*/  enterblock (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incr_top (TYPE_3__*) ; 
 int /*<<< orphan*/  luaH_new (TYPE_3__*) ; 
 int /*<<< orphan*/  sethvalue2s (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void open_func (LexState *ls, FuncState *fs, BlockCnt *bl) {
  lua_State *L = ls->L;
  Proto *f;
  fs->prev = ls->fs;  /* linked list of funcstates */
  fs->ls = ls;
  ls->fs = fs;
  fs->pc = 0;
  fs->lasttarget = 0;
  fs->jpc = NO_JUMP;
  fs->freereg = 0;
  fs->nk = 0;
  fs->np = 0;
  fs->nups = 0;
  fs->nlocvars = 0;
  fs->nactvar = 0;
  fs->firstlocal = ls->dyd->actvar.n;
  fs->bl = NULL;
  f = fs->f;
  f->source = ls->source;
  f->maxstacksize = 2;  /* registers 0/1 are always valid */
  fs->h = luaH_new(L);
  /* anchor table of constants (to avoid being collected) */
  sethvalue2s(L, L->top, fs->h);
  incr_top(L);
  enterblock(fs, bl, 0);
}