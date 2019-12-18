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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int LUA_OPADD ; 
#define  LUA_OPBAND 135 
#define  LUA_OPBNOT 134 
#define  LUA_OPBOR 133 
#define  LUA_OPBXOR 132 
#define  LUA_OPDIV 131 
#define  LUA_OPPOW 130 
#define  LUA_OPSHL 129 
#define  LUA_OPSHR 128 
 int /*<<< orphan*/  TMS ; 
 int TM_ADD ; 
 int /*<<< orphan*/  cast (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intarith (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaT_trybinTM (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numarith (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfltvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setivalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tointeger (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tonumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttisinteger (int /*<<< orphan*/  const*) ; 

void luaO_arith (lua_State *L, int op, const TValue *p1, const TValue *p2,
                 TValue *res) {
  switch (op) {
    case LUA_OPBAND: case LUA_OPBOR: case LUA_OPBXOR:
    case LUA_OPSHL: case LUA_OPSHR:
    case LUA_OPBNOT: {  /* operate only on integers */
      lua_Integer i1; lua_Integer i2;
      if (tointeger(p1, &i1) && tointeger(p2, &i2)) {
        setivalue(res, intarith(L, op, i1, i2));
        return;
      }
      else break;  /* go to the end */
    }
    case LUA_OPDIV: case LUA_OPPOW: {  /* operate only on floats */
      lua_Number n1; lua_Number n2;
      if (tonumber(p1, &n1) && tonumber(p2, &n2)) {
        setfltvalue(res, numarith(L, op, n1, n2));
        return;
      }
      else break;  /* go to the end */
    }
    default: {  /* other operations */
      lua_Number n1; lua_Number n2;
      if (ttisinteger(p1) && ttisinteger(p2)) {
        setivalue(res, intarith(L, op, ivalue(p1), ivalue(p2)));
        return;
      }
      else if (tonumber(p1, &n1) && tonumber(p2, &n2)) {
        setfltvalue(res, numarith(L, op, n1, n2));
        return;
      }
      else break;  /* go to the end */
    }
  }
  /* could not perform raw operation; try metamethod */
  lua_assert(L != NULL);  /* should not fail when folding (compile time) */
  luaT_trybinTM(L, p1, p2, res, cast(TMS, (op - LUA_OPADD) + TM_ADD));
}