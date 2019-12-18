#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ gcstate; scalar_t__ tobefnz; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int GCFINALIZENUM ; 
 scalar_t__ GCSpause ; 
 int /*<<< orphan*/  GCTM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  generationalcollection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incstep (int /*<<< orphan*/ *) ; 
 scalar_t__ isgenerational (TYPE_1__*) ; 

void luaC_forcestep (lua_State *L) {
  global_State *g = G(L);
  int i;
  if (isgenerational(g)) generationalcollection(L);
  else incstep(L);
  /* run a few finalizers (or all of them at the end of a collect cycle) */
  for (i = 0; g->tobefnz && (i < GCFINALIZENUM || g->gcstate == GCSpause); i++)
    GCTM(L, 1);  /* call one finalizer */
}