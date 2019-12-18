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
 int UCL_EMIT_JSON ; 
 int UCL_EMIT_JSON_COMPACT ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ucl_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ucl_object_lua_import (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lua_ucl_to_json (lua_State *L)
{
	ucl_object_t *obj;
	int format = UCL_EMIT_JSON;

	if (lua_gettop (L) > 1) {
		if (lua_toboolean (L, 2)) {
			format = UCL_EMIT_JSON_COMPACT;
		}
	}

	obj = ucl_object_lua_import (L, 1);
	if (obj != NULL) {
		lua_ucl_to_string (L, obj, format);
		ucl_object_unref (obj);
	}
	else {
		lua_pushnil (L);
	}

	return 1;
}