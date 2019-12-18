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
typedef  enum ucl_emitter { ____Placeholder_ucl_emitter } ucl_emitter ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 int UCL_EMIT_JSON_COMPACT ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_ucl_object_get (int /*<<< orphan*/ *,int) ; 
 int lua_ucl_str_to_emit_type (char const*) ; 
 int lua_ucl_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lua_ucl_object_tostring (lua_State *L)
{
	ucl_object_t *obj;
	enum ucl_emitter format = UCL_EMIT_JSON_COMPACT;

	obj = lua_ucl_object_get (L, 1);

	if (obj) {
		if (lua_gettop (L) > 1) {
			if (lua_type (L, 2) == LUA_TSTRING) {
				const char *strtype = lua_tostring (L, 2);

				format = lua_ucl_str_to_emit_type (strtype);
			}
		}

		return lua_ucl_to_string (L, obj, format);
	}
	else {
		lua_pushnil (L);
	}

	return 1;
}