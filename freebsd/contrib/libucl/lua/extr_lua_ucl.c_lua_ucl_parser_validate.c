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
struct ucl_schema_error {int /*<<< orphan*/  msg; } ;
struct ucl_parser {scalar_t__ top_obj; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 scalar_t__ LUA_TTABLE ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 struct ucl_parser* lua_ucl_parser_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ucl_object_lua_import (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_object_validate (int /*<<< orphan*/ *,scalar_t__,struct ucl_schema_error*) ; 
 int /*<<< orphan*/  ucl_parser_add_file (struct ucl_parser*,char const*) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 int /*<<< orphan*/  ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/ * ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lua_ucl_parser_validate (lua_State *L)
{
	struct ucl_parser *parser, *schema_parser;
	ucl_object_t *schema;
	const char *schema_file;
	struct ucl_schema_error err;

	parser = lua_ucl_parser_get (L, 1);

	if (parser && parser->top_obj) {
		if (lua_type (L, 2) == LUA_TTABLE) {
			schema = ucl_object_lua_import (L, 2);

			if (schema == NULL) {
				lua_pushboolean (L, false);
				lua_pushstring (L, "cannot load schema from lua table");

				return 2;
			}
		}
		else if (lua_type (L, 2) == LUA_TSTRING) {
			schema_parser = ucl_parser_new (0);
			schema_file = luaL_checkstring (L, 2);

			if (!ucl_parser_add_file (schema_parser, schema_file)) {
				lua_pushboolean (L, false);
				lua_pushfstring (L, "cannot parse schema file \"%s\": "
						"%s", schema_file, ucl_parser_get_error (parser));
				ucl_parser_free (schema_parser);

				return 2;
			}

			schema = ucl_parser_get_object (schema_parser);
			ucl_parser_free (schema_parser);
		}
		else {
			lua_pushboolean (L, false);
			lua_pushstring (L, "invalid schema argument");

			return 2;
		}

		if (!ucl_object_validate (schema, parser->top_obj, &err)) {
			lua_pushboolean (L, false);
			lua_pushfstring (L, "validation error: "
					"%s", err.msg);
		}
		else {
			lua_pushboolean (L, true);
			lua_pushnil (L);
		}

		ucl_object_unref (schema);
	}
	else {
		lua_pushboolean (L, false);
		lua_pushstring (L, "invalid parser or empty top object");
	}

	return 2;
}