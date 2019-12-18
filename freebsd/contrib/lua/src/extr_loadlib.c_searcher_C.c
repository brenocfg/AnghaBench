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
 int /*<<< orphan*/  LUA_CSUBSEP ; 
 int checkload (int /*<<< orphan*/ *,int,char const*) ; 
 char* findfile (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ loadfunc (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int searcher_C (lua_State *L) {
  const char *name = luaL_checkstring(L, 1);
  const char *filename = findfile(L, name, "cpath", LUA_CSUBSEP);
  if (filename == NULL) return 1;  /* module not found in this path */
  return checkload(L, (loadfunc(L, filename, name) == 0), filename);
}