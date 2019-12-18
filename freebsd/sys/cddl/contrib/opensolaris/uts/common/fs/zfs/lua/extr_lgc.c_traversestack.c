#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_7__ {int stacksize; TYPE_3__* ci; TYPE_3__ base_ci; int /*<<< orphan*/ * stack; int /*<<< orphan*/ * top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int lu_mem ;
struct TYPE_8__ {scalar_t__ gcstate; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/ * StkId ;
typedef  TYPE_3__ CallInfo ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 int /*<<< orphan*/  markvalue (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static lu_mem traversestack (global_State *g, lua_State *th) {
  int n = 0;
  StkId o = th->stack;
  if (o == NULL)
    return 1;  /* stack not completely built yet */
  for (; o < th->top; o++)  /* mark live elements in the stack */
    markvalue(g, o);
  if (g->gcstate == GCSatomic) {  /* final traversal? */
    StkId lim = th->stack + th->stacksize;  /* real end of stack */
    for (; o < lim; o++)  /* clear not-marked stack slice */
      setnilvalue(o);
  }
  else {  /* count call infos to compute size */
    CallInfo *ci;
    for (ci = &th->base_ci; ci != th->ci; ci = ci->next)
      n++;
  }
  return sizeof(lua_State) + sizeof(TValue) * th->stacksize +
         sizeof(CallInfo) * n;
}