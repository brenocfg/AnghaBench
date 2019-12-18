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
struct ucl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 struct ucl_parser* lua_ucl_parser_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ucl_parser_add_file (struct ucl_parser*,char const*) ; 
 char* ucl_parser_get_error (struct ucl_parser*) ; 

__attribute__((used)) static int
lua_ucl_parser_parse_file (lua_State *L)
{
	struct ucl_parser *parser;
	const char *file;
	int ret = 2;

	parser = lua_ucl_parser_get (L, 1);
	file = luaL_checkstring (L, 2);

	if (parser != NULL && file != NULL) {
		if (ucl_parser_add_file (parser, file)) {
			lua_pushboolean (L, true);
			ret = 1;
		}
		else {
			lua_pushboolean (L, false);
			lua_pushstring (L, ucl_parser_get_error (parser));
		}
	}
	else {
		lua_pushboolean (L, false);
		lua_pushstring (L, "invalid arguments");
	}

	return ret;
}