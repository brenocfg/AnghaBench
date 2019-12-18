#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct interp_lua_softc {int /*<<< orphan*/ * luap; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {scalar_t__ func; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  LDBG (char*) ; 
 char* LOADER_LUA ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ interp_include (char const*) ; 
 int /*<<< orphan*/  interp_lua_realloc ; 
 TYPE_1__* loadedlibs ; 
 int /*<<< orphan*/  luaL_requiref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/ * lua_newstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 struct interp_lua_softc lua_softc ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

void
interp_init(void)
{
	lua_State *luap;
	struct interp_lua_softc	*softc = &lua_softc;
	const char *filename;
	const luaL_Reg *lib;

	setenv("script.lang", "lua", 1);
	LDBG("creating context");

	luap = lua_newstate(interp_lua_realloc, NULL);
	if (luap == NULL) {
		printf("problem initializing the Lua interpreter\n");
		abort();
	}
	softc->luap = luap;

	/* "require" functions from 'loadedlibs' and set results to global table */
	for (lib = loadedlibs; lib->func; lib++) {
		luaL_requiref(luap, lib->name, lib->func, 1);
		lua_pop(luap, 1);  /* remove lib */
	}

	filename = LOADER_LUA;
	if (interp_include(filename) != 0) {
                const char *errstr = lua_tostring(luap, -1);
                errstr = errstr == NULL ? "unknown" : errstr;
                printf("Startup error in %s:\nLUA ERROR: %s.\n", filename, errstr);
                lua_pop(luap, 1);
	}
}