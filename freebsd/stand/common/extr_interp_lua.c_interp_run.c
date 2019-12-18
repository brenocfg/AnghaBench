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
struct interp_lua_softc {int /*<<< orphan*/ * luap; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int /*<<< orphan*/  LDBG (char*) ; 
 char* command_errmsg ; 
 int /*<<< orphan*/  free (char**) ; 
 int interp_builtin_cmd (int,char**) ; 
 int luaL_dostring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 struct interp_lua_softc lua_softc ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ parse (int*,char***,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
interp_run(const char *line)
{
	int	argc, nargc;
	char	**argv;
	lua_State *luap;
	struct interp_lua_softc	*softc = &lua_softc;
	int status, ret;

	luap = softc->luap;
	LDBG("executing line...");
	if ((status = luaL_dostring(luap, line)) != 0) {
                lua_pop(luap, 1);
		/*
		 * The line wasn't executable as lua; run it through parse to
		 * to get consistent parsing of command line arguments, then
		 * run it through cli_execute. If that fails, then we'll try it
		 * as a builtin.
		 */
		command_errmsg = NULL;
		if (parse(&argc, &argv, line) == 0) {
			lua_getglobal(luap, "cli_execute");
			for (nargc = 0; nargc < argc; ++nargc) {
				lua_pushstring(luap, argv[nargc]);
			}
			status = lua_pcall(luap, argc, 1, 0);
			ret = lua_tointeger(luap, 1);
			lua_pop(luap, 1);
			if (status != 0 || ret != 0) {
				/*
				 * Lua cli_execute will pass the function back
				 * through loader.command, which is a proxy to
				 * interp_builtin_cmd. If we failed to interpret
				 * the command, though, then there's a chance
				 * that didn't happen. Call interp_builtin_cmd
				 * directly if our lua_pcall was not successful.
				 */
				status = interp_builtin_cmd(argc, argv);
			}
			if (status != 0) {
				if (command_errmsg != NULL)
					printf("%s\n", command_errmsg);
				else
					printf("Command failed\n");
				status = CMD_ERROR;
			}
			free(argv);
		} else {
			printf("Failed to parse \'%s\'\n", line);
			status = CMD_ERROR;
		}
	}

	return (status == 0 ? CMD_OK : CMD_ERROR);
}