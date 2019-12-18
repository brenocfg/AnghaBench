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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_METATABLE ; 
 int /*<<< orphan*/  closedir (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dirent* readdirfd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lua_dir_iter_next(lua_State *L)
{
	struct dirent *entry;
	DIR *dp, **dpp;

	dpp = (DIR **)luaL_checkudata(L, 1, DIR_METATABLE);
	dp = *dpp;
	luaL_argcheck(L, dp != NULL, 1, "closed directory");

	entry = readdirfd(dp->fd);
	if (entry == NULL) {
		closedir(dp);
		*dpp = NULL;
		return 0;
	}

	lua_pushstring(L, entry->d_name);
	return 1;
}