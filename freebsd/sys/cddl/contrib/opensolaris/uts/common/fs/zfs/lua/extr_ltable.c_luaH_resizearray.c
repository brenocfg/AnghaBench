#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 scalar_t__ isdummy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_resize (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int sizenode (TYPE_1__*) ; 

void luaH_resizearray (lua_State *L, Table *t, int nasize) {
  int nsize = isdummy(t->node) ? 0 : sizenode(t);
  luaH_resize(L, t, nasize, nsize);
}