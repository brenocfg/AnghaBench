#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lu_mem ;
struct TYPE_7__ {int size; int /*<<< orphan*/ * hash; } ;
struct TYPE_8__ {int gcstate; int GCmemtrav; int GCestimate; int sweepstrgc; int /*<<< orphan*/  mainthread; int /*<<< orphan*/ ** sweepgc; int /*<<< orphan*/ ** sweepfin; TYPE_1__ strt; int /*<<< orphan*/  gray; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int GCSWEEPCOST ; 
 int GCSWEEPMAX ; 
 int GCSatomic ; 
#define  GCSpause 132 
#define  GCSpropagate 131 
#define  GCSsweep 130 
#define  GCSsweepstring 129 
#define  GCSsweepudata 128 
 int atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkSizes (int /*<<< orphan*/ *) ; 
 int entersweep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isgenerational (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagatemark (TYPE_2__*) ; 
 int /*<<< orphan*/  restartcollection (TYPE_2__*) ; 
 void* sweeplist (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lu_mem singlestep (lua_State *L) {
  global_State *g = G(L);
  switch (g->gcstate) {
    case GCSpause: {
      /* start to count memory traversed */
      g->GCmemtrav = g->strt.size * sizeof(GCObject*);
      lua_assert(!isgenerational(g));
      restartcollection(g);
      g->gcstate = GCSpropagate;
      return g->GCmemtrav;
    }
    case GCSpropagate: {
      if (g->gray) {
        lu_mem oldtrav = g->GCmemtrav;
        propagatemark(g);
        return g->GCmemtrav - oldtrav;  /* memory traversed in this step */
      }
      else {  /* no more `gray' objects */
        lu_mem work;
        int sw;
        g->gcstate = GCSatomic;  /* finish mark phase */
        g->GCestimate = g->GCmemtrav;  /* save what was counted */;
        work = atomic(L);  /* add what was traversed by 'atomic' */
        g->GCestimate += work;  /* estimate of total memory traversed */
        sw = entersweep(L);
        return work + sw * GCSWEEPCOST;
      }
    }
    case GCSsweepstring: {
      int i;
      for (i = 0; i < GCSWEEPMAX && g->sweepstrgc + i < g->strt.size; i++)
        sweepwholelist(L, &g->strt.hash[g->sweepstrgc + i]);
      g->sweepstrgc += i;
      if (g->sweepstrgc >= g->strt.size)  /* no more strings to sweep? */
        g->gcstate = GCSsweepudata;
      return i * GCSWEEPCOST;
    }
    case GCSsweepudata: {
      if (g->sweepfin) {
        g->sweepfin = sweeplist(L, g->sweepfin, GCSWEEPMAX);
        return GCSWEEPMAX*GCSWEEPCOST;
      }
      else {
        g->gcstate = GCSsweep;
        return 0;
      }
    }
    case GCSsweep: {
      if (g->sweepgc) {
        g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
        return GCSWEEPMAX*GCSWEEPCOST;
      }
      else {
        /* sweep main thread */
        GCObject *mt = obj2gco(g->mainthread);
        sweeplist(L, &mt, 1);
        checkSizes(L);
        g->gcstate = GCSpause;  /* finish collection */
        return GCSWEEPCOST;
      }
    }
    default: lua_assert(0); return 0;
  }
}