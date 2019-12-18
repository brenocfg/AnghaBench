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
struct ucl_lua_funcdata {struct ucl_lua_funcdata* ret; int /*<<< orphan*/  idx; int /*<<< orphan*/  L; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (struct ucl_lua_funcdata*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lua_ucl_userdata_dtor (void *ud)
{
	struct ucl_lua_funcdata *fd = (struct ucl_lua_funcdata *)ud;

	luaL_unref (fd->L, LUA_REGISTRYINDEX, fd->idx);
	if (fd->ret != NULL) {
		free (fd->ret);
	}
	free (fd);
}