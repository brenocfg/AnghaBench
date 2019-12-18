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
struct TYPE_6__ {scalar_t__ status; TYPE_2__* ci; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  extra; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  StkId ;
typedef  TYPE_2__ CallInfo ;

/* Variables and functions */
 scalar_t__ LUA_YIELD ; 
 int /*<<< orphan*/  restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swapextra (lua_State *L) {
  if (L->status == LUA_YIELD) {
    CallInfo *ci = L->ci;  /* get function that yielded */
    StkId temp = ci->func;  /* exchange its 'func' and 'extra' values */
    ci->func = restorestack(L, ci->extra);
    ci->extra = savestack(L, temp);
  }
}