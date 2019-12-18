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
 scalar_t__ luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 char** malloc (int) ; 

__attribute__((used)) static int
lua_command(lua_State *L)
{
	int	i;
	int	res = 1;
	int 	argc = lua_gettop(L);
	char	**argv;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		return 0;
	for (i = 0; i < argc; i++)
		argv[i] = (char *)(intptr_t)luaL_checkstring(L, i + 1);
	argv[argc] = NULL;
	res = interp_builtin_cmd(argc, argv);
	free(argv);
	lua_pushinteger(L, res);

	return 1;
}