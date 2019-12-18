#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ matchdepth; char const* src_init; char const* src_end; char const* p_end; scalar_t__ level; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ MatchState ;

/* Variables and functions */
 scalar_t__ MAXCCALLS ; 
 char* lmemfind (char const*,size_t,char const*,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* match (TYPE_1__*,char const*,char const*) ; 
 scalar_t__ nospecials (char const*,size_t) ; 
 size_t posrelat (int /*<<< orphan*/ ,size_t) ; 
 int push_captures (TYPE_1__*,char const*,char const*) ; 

__attribute__((used)) static int str_find_aux (lua_State *L, int find) {
  size_t ls, lp;
  const char *s = luaL_checklstring(L, 1, &ls);
  const char *p = luaL_checklstring(L, 2, &lp);
  size_t init = posrelat(luaL_optinteger(L, 3, 1), ls);
  if (init < 1) init = 1;
  else if (init > ls + 1) {  /* start after string's end? */
    lua_pushnil(L);  /* cannot find anything */
    return 1;
  }
  /* explicit request or no special characters? */
  if (find && (lua_toboolean(L, 4) || nospecials(p, lp))) {
    /* do a plain search */
    const char *s2 = lmemfind(s + init - 1, ls - init + 1, p, lp);
    if (s2) {
      lua_pushinteger(L, s2 - s + 1);
      lua_pushinteger(L, s2 - s + lp);
      return 2;
    }
  }
  else {
    MatchState ms;
    const char *s1 = s + init - 1;
    int anchor = (*p == '^');
    if (anchor) {
      p++; lp--;  /* skip anchor character */
    }
    ms.L = L;
    ms.matchdepth = MAXCCALLS;
    ms.src_init = s;
    ms.src_end = s + ls;
    ms.p_end = p + lp;
    do {
      const char *res;
      ms.level = 0;
      lua_assert(ms.matchdepth == MAXCCALLS);
      if ((res=match(&ms, s1, p)) != NULL) {
        if (find) {
          lua_pushinteger(L, s1 - s + 1);  /* start */
          lua_pushinteger(L, res - s);   /* end */
          return push_captures(&ms, NULL, 0) + 2;
        }
        else
          return push_captures(&ms, s1, res);
      }
    } while (s1++ < ms.src_end && !anchor);
  }
  lua_pushnil(L);  /* not found */
  return 1;
}