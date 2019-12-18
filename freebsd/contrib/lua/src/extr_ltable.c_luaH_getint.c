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
typedef  int lua_Integer ;
struct TYPE_4__ {int sizearray; int /*<<< orphan*/  const* array; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int gnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* gval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hashint (TYPE_1__*,int) ; 
 int ivalue (int /*<<< orphan*/ ) ; 
 int l_castS2U (int) ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 scalar_t__ ttisinteger (int /*<<< orphan*/ ) ; 

const TValue *luaH_getint (Table *t, lua_Integer key) {
  /* (1 <= key && key <= t->sizearray) */
  if (l_castS2U(key) - 1 < t->sizearray)
    return &t->array[key - 1];
  else {
    Node *n = hashint(t, key);
    for (;;) {  /* check whether 'key' is somewhere in the chain */
      if (ttisinteger(gkey(n)) && ivalue(gkey(n)) == key)
        return gval(n);  /* that's it */
      else {
        int nx = gnext(n);
        if (nx == 0) break;
        n += nx;
      }
    }
    return luaO_nilobject;
  }
}