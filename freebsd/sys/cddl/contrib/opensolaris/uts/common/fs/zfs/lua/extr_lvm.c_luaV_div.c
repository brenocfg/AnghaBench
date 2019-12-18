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
typedef  scalar_t__ n ;
typedef  unsigned int lua_Unsigned ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  luaG_runerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static lua_Number luaV_div (lua_State *L, lua_Number m, lua_Number n) {
  if ((lua_Unsigned)(n) + 1u <= 1u) {  /* special cases: -1 or 0 */
    if (n == 0)
      luaG_runerror(L, "attempt to divide by zero");
    return (0 - m);   /* n==-1; avoid overflow with 0x80000...//-1 */
  }
  else {
    lua_Number q = m / n;  /* perform C division */
    if ((m ^ n) < 0 && m % n != 0)  /* 'm/n' would be negative non-integer? */
      q -= 1;  /* correct result for different rounding */
    return q;
  }
}