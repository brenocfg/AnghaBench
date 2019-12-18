#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * openupval; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_21__ {int /*<<< orphan*/ * allgc; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_19__ {int /*<<< orphan*/  value; } ;
struct TYPE_22__ {scalar_t__ v; TYPE_1__ u; int /*<<< orphan*/ * next; } ;
typedef  TYPE_4__ UpVal ;
struct TYPE_18__ {int /*<<< orphan*/ * next; } ;
typedef  scalar_t__ StkId ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_3__* G (TYPE_2__*) ; 
 TYPE_15__* gch (int /*<<< orphan*/ *) ; 
 TYPE_4__* gco2uv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isblack (int /*<<< orphan*/ *) ; 
 scalar_t__ isdead (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaC_checkupvalcolor (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  luaF_freeupval (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * obj2gco (TYPE_4__*) ; 
 int /*<<< orphan*/  setobj (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlinkupval (TYPE_4__*) ; 

void luaF_close (lua_State *L, StkId level) {
  UpVal *uv;
  global_State *g = G(L);
  while (L->openupval != NULL && (uv = gco2uv(L->openupval))->v >= level) {
    GCObject *o = obj2gco(uv);
    lua_assert(!isblack(o) && uv->v != &uv->u.value);
    L->openupval = uv->next;  /* remove from `open' list */
    if (isdead(g, o))
      luaF_freeupval(L, uv);  /* free upvalue */
    else {
      unlinkupval(uv);  /* remove upvalue from 'uvhead' list */
      setobj(L, &uv->u.value, uv->v);  /* move value to upvalue slot */
      uv->v = &uv->u.value;  /* now current value lives here */
      gch(o)->next = g->allgc;  /* link upvalue into 'allgc' list */
      g->allgc = o;
      luaC_checkupvalcolor(g, uv);
    }
  }
}