#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Table ;
struct TYPE_6__ {scalar_t__ tt; } ;
struct TYPE_7__ {TYPE_1__ tsv; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ TString ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ LUA_TSHRSTR ; 
 scalar_t__ eqshrstr (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* gval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hashstr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/ ) ; 
 scalar_t__ ttisshrstring (int /*<<< orphan*/ ) ; 

const TValue *luaH_getstr (Table *t, TString *key) {
  Node *n = hashstr(t, key);
  lua_assert(key->tsv.tt == LUA_TSHRSTR);
  do {  /* check whether `key' is somewhere in the chain */
    if (ttisshrstring(gkey(n)) && eqshrstr(rawtsvalue(gkey(n)), key))
      return gval(n);  /* that's it */
    else n = gnext(n);
  } while (n);
  return luaO_nilobject;
}