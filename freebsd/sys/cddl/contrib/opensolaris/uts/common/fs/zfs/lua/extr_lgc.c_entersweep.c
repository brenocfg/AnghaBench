#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  allgc; int /*<<< orphan*/ * sweepgc; int /*<<< orphan*/  finobj; int /*<<< orphan*/ * sweepfin; scalar_t__ sweepstrgc; int /*<<< orphan*/  gcstate; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSsweepstring ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 void* sweeptolive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int entersweep (lua_State *L) {
  global_State *g = G(L);
  int n = 0;
  g->gcstate = GCSsweepstring;
  lua_assert(g->sweepgc == NULL && g->sweepfin == NULL);
  /* prepare to sweep strings, finalizable objects, and regular objects */
  g->sweepstrgc = 0;
  g->sweepfin = sweeptolive(L, &g->finobj, &n);
  g->sweepgc = sweeptolive(L, &g->allgc, &n);
  return n;
}