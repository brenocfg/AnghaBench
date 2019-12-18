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
struct ucl_lua_funcdata {char const* ret; int /*<<< orphan*/  L; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ ,int) ; 
 char const* strdup (char const*) ; 

__attribute__((used)) static const char *
lua_ucl_userdata_emitter (void *ud)
{
	struct ucl_lua_funcdata *fd = (struct ucl_lua_funcdata *)ud;
	const char *out = "";

	lua_rawgeti (fd->L, LUA_REGISTRYINDEX, fd->idx);

	lua_pcall (fd->L, 0, 1, 0);
	out = lua_tostring (fd->L, -1);

	if (out != NULL) {
		/* We need to store temporary string in a more appropriate place */
		if (fd->ret) {
			free (fd->ret);
		}
		fd->ret = strdup (out);
	}

	lua_settop (fd->L, 0);

	return fd->ret;
}