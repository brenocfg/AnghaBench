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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  (* push ) (int /*<<< orphan*/ *,struct stat*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* members ; 
 size_t nitems (TYPE_1__*) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct stat*) ; 

__attribute__((used)) static int
lua_attributes(lua_State *L)
{
	struct stat sb;
	const char *path, *member;
	size_t i;
	int rc;

	path = luaL_checkstring(L, 1);
	if (path == NULL) {
		lua_pushnil(L);
		lua_pushfstring(L, "cannot convert first argument to string");
		lua_pushinteger(L, EINVAL);
		return 3;
	}

	rc = stat(path, &sb);
	if (rc != 0) {
		lua_pushnil(L);
		lua_pushfstring(L,
		    "cannot obtain information from file '%s': %s", path,
		    strerror(errno));
		lua_pushinteger(L, errno);
		return 3;
	}

	if (lua_isstring(L, 2)) {
		member = lua_tostring(L, 2);
		for (i = 0; i < nitems(members); i++) {
			if (strcmp(members[i].name, member) != 0)
				continue;

			members[i].push(L, &sb);
			return 1;
		}
		return luaL_error(L, "invalid attribute name '%s'", member);
	}

	/* Create or reuse existing table */
	lua_settop(L, 2);
	if (!lua_istable(L, 2))
		lua_newtable(L);

	/* Export all stat data to caller */
	for (i = 0; i < nitems(members); i++) {
		lua_pushstring(L, members[i].name);
		members[i].push(L, &sb);
		lua_rawset(L, -3);
	}
	return 1;
}