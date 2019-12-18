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
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (char const*,char const*,int) ; 

__attribute__((used)) static int
lua_setenv(lua_State *L)
{
	const char *key, *val;

	key = luaL_checkstring(L, 1);
	val = luaL_checkstring(L, 2);
	lua_pushinteger(L, setenv(key, val, 1));

	return 1;
}