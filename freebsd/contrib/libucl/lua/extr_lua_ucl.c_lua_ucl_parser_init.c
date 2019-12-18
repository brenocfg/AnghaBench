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
typedef  int /*<<< orphan*/  parser ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  PARSER_META ; 
 int UCL_PARSER_NO_FILEVARS ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 struct ucl_parser** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 struct ucl_parser* ucl_parser_new (int) ; 

__attribute__((used)) static int
lua_ucl_parser_init (lua_State *L)
{
	struct ucl_parser *parser, **pparser;
	int flags = UCL_PARSER_NO_FILEVARS;

	if (lua_gettop (L) >= 1) {
		flags = lua_tonumber (L, 1);
	}

	parser = ucl_parser_new (flags);
	if (parser == NULL) {
		lua_pushnil (L);
	}

	pparser = lua_newuserdata (L, sizeof (parser));
	*pparser = parser;
	luaL_getmetatable (L, PARSER_META);
	lua_setmetatable (L, -2);

	return 1;
}