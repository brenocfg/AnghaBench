#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TTABLE 128 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ucl_object_lua_fromelt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ucl_object_lua_fromtable (int /*<<< orphan*/ *,int) ; 

ucl_object_t *
ucl_object_lua_import (lua_State *L, int idx)
{
	ucl_object_t *obj;
	int t;

	t = lua_type (L, idx);
	switch (t) {
	case LUA_TTABLE:
		obj = ucl_object_lua_fromtable (L, idx);
		break;
	default:
		obj = ucl_object_lua_fromelt (L, idx);
		break;
	}

	return obj;
}