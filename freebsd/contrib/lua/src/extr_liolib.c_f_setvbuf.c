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
typedef  scalar_t__ lua_Integer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LUAL_BUFFERSIZE ; 
#define  _IOFBF 130 
#define  _IOLBF 129 
#define  _IONBF 128 
 int luaL_checkoption (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const* const*) ; 
 int luaL_fileresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,size_t) ; 
 int /*<<< orphan*/ * tofile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f_setvbuf (lua_State *L) {
  static const int mode[] = {_IONBF, _IOFBF, _IOLBF};
  static const char *const modenames[] = {"no", "full", "line", NULL};
  FILE *f = tofile(L);
  int op = luaL_checkoption(L, 2, NULL, modenames);
  lua_Integer sz = luaL_optinteger(L, 3, LUAL_BUFFERSIZE);
  int res = setvbuf(f, NULL, mode[op], (size_t)sz);
  return luaL_fileresult(L, res == 0, NULL);
}