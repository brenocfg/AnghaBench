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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ parse (int*,char***,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lua_parse(lua_State *L)
{
	int	argc, nargc;
	char	**argv;

	if (parse(&argc, &argv, luaL_checkstring(L, 1)) == 0) {
		for (nargc = 0; nargc < argc; ++nargc) {
			lua_pushstring(L, argv[nargc]);
		}
		free(argv);
		return nargc;
	}

	lua_pushnil(L);
	return 1;
}