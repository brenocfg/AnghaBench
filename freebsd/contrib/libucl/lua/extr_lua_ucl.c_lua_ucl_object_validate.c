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
struct ucl_schema_error {char const* msg; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 scalar_t__ LUA_TTABLE ; 
 scalar_t__ LUA_TUSERDATA ; 
 scalar_t__ UCL_OBJECT ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_ucl_object_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ucl_push_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucl_object_lookup_path_char (int /*<<< orphan*/ *,char const*,char) ; 
 scalar_t__ ucl_object_type (int /*<<< orphan*/ *) ; 
 int ucl_object_validate_root_ext (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ucl_schema_error*) ; 

__attribute__((used)) static int
lua_ucl_object_validate (lua_State *L)
{
	ucl_object_t *obj, *schema, *ext_refs = NULL;
	const ucl_object_t *schema_elt;
	bool res = false;
	struct ucl_schema_error err;
	const char *path = NULL;

	obj = lua_ucl_object_get (L, 1);
	schema = lua_ucl_object_get (L, 2);

	if (schema && obj && ucl_object_type (schema) == UCL_OBJECT) {
		if (lua_gettop (L) > 2) {
			if (lua_type (L, 3) == LUA_TSTRING) {
				path = lua_tostring (L, 3);
				if (path[0] == '#') {
					path++;
				}
			}
			else if (lua_type (L, 3) == LUA_TUSERDATA || lua_type (L, 3) ==
						LUA_TTABLE) {
				/* External refs */
				ext_refs = lua_ucl_object_get (L, 3);
			}

			if (lua_gettop (L) > 3) {
				if (lua_type (L, 4) == LUA_TUSERDATA || lua_type (L, 4) ==
						LUA_TTABLE) {
					/* External refs */
					ext_refs = lua_ucl_object_get (L, 4);
				}
			}
		}

		if (path) {
			schema_elt = ucl_object_lookup_path_char (schema, path, '/');
		}
		else {
			/* Use the top object */
			schema_elt = schema;
		}

		if (schema_elt) {
			res = ucl_object_validate_root_ext (schema_elt, obj, schema,
					ext_refs, &err);

			if (res) {
				lua_pushboolean (L, res);
				lua_pushnil (L);

				if (ext_refs) {
					lua_ucl_push_opaque (L, ext_refs);
				}
			}
			else {
				lua_pushboolean (L, res);
				lua_pushfstring (L, "validation error: %s", err.msg);

				if (ext_refs) {
					lua_ucl_push_opaque (L, ext_refs);
				}
			}
		}
		else {
			lua_pushboolean (L, res);

			lua_pushfstring (L, "cannot find the requested path: %s", path);

			if (ext_refs) {
				lua_ucl_push_opaque (L, ext_refs);
			}
		}
	}
	else {
		lua_pushboolean (L, res);
		lua_pushstring (L, "invalid object or schema");
	}

	if (ext_refs) {
		return 3;
	}

	return 2;
}