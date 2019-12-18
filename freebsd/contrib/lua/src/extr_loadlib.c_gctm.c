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
typedef  int lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  lsys_unloadlib (int /*<<< orphan*/ ) ; 
 int luaL_len (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gctm (lua_State *L) {
  lua_Integer n = luaL_len(L, 1);
  for (; n >= 1; n--) {  /* for each handle, in reverse order */
    lua_rawgeti(L, 1, n);  /* get handle CLIBS[n] */
    lsys_unloadlib(lua_touserdata(L, -1));
    lua_pop(L, 1);  /* pop handle */
  }
  return 0;
}