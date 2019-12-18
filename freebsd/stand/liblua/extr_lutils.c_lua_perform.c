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
 int interp_builtin_cmd (int,char**) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ parse (int*,char***,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lua_perform(lua_State *L)
{
	int	argc;
	char	**argv;
	int	res = 1;

	if (parse(&argc, &argv, luaL_checkstring(L, 1)) == 0) {
		res = interp_builtin_cmd(argc, argv);
		free(argv);
	}
	lua_pushinteger(L, res);

	return 1;
}