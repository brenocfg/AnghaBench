#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int linenumber; TYPE_1__* dyd; int /*<<< orphan*/  L; } ;
struct TYPE_9__ {int /*<<< orphan*/  gt; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_GOTO ; 
 int /*<<< orphan*/  findlabel (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * luaS_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int newlabelentry (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * str_checkname (TYPE_2__*) ; 
 scalar_t__ testnext (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gotostat (LexState *ls, int pc) {
  int line = ls->linenumber;
  TString *label;
  int g;
  if (testnext(ls, TK_GOTO))
    label = str_checkname(ls);
  else {
    luaX_next(ls);  /* skip break */
    label = luaS_new(ls->L, "break");
  }
  g = newlabelentry(ls, &ls->dyd->gt, label, line, pc);
  findlabel(ls, g);  /* close it if label already defined */
}