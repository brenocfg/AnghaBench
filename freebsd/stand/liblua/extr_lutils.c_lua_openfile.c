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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lua_openfile(lua_State *L)
{
	const char	*mode, *str;
	int	nargs;

	nargs = lua_gettop(L);
	if (nargs < 1 || nargs > 2) {
		lua_pushnil(L);
		return 1;
	}
	str = lua_tostring(L, 1);
	mode = "r";
	if (nargs > 1) {
		mode = lua_tostring(L, 2);
		if (mode == NULL) {
			lua_pushnil(L);
			return 1;
		}
	}
	FILE * f = fopen(str, mode);
	if (f != NULL) {
		FILE ** ptr = (FILE**)lua_newuserdata(L, sizeof(FILE**));
		*ptr = f;
	} else
		lua_pushnil(L);
	return 1;
}