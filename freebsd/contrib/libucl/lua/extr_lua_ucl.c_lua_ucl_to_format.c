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
 scalar_t__ LUA_TNUMBER ; 
 scalar_t__ LUA_TSTRING ; 
 int UCL_EMIT_CONFIG ; 
 int UCL_EMIT_JSON ; 
 int UCL_EMIT_JSON_COMPACT ; 
 int UCL_EMIT_MSGPACK ; 
 int UCL_EMIT_YAML ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ucl_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/ * ucl_object_lua_import (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lua_ucl_to_format (lua_State *L)
{
	ucl_object_t *obj;
	int format = UCL_EMIT_JSON;

	if (lua_gettop (L) > 1) {
		if (lua_type (L, 2) == LUA_TNUMBER) {
			format = lua_tonumber (L, 2);
			if (format < 0 || format >= UCL_EMIT_YAML) {
				lua_pushnil (L);
				return 1;
			}
		}
		else if (lua_type (L, 2) == LUA_TSTRING) {
			const char *strtype = lua_tostring (L, 2);

			if (strcasecmp (strtype, "json") == 0) {
				format = UCL_EMIT_JSON;
			}
			else if (strcasecmp (strtype, "json-compact") == 0) {
				format = UCL_EMIT_JSON_COMPACT;
			}
			else if (strcasecmp (strtype, "yaml") == 0) {
				format = UCL_EMIT_YAML;
			}
			else if (strcasecmp (strtype, "config") == 0 ||
				strcasecmp (strtype, "ucl") == 0) {
				format = UCL_EMIT_CONFIG;
			}
			else if (strcasecmp (strtype, "msgpack") == 0) {
				format = UCL_EMIT_MSGPACK;
			}
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