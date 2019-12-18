#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ k; } ;
typedef  TYPE_1__ expdesc ;
struct TYPE_12__ {int /*<<< orphan*/ * envn; int /*<<< orphan*/ * fs; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ VLOCAL ; 
 scalar_t__ VUPVAL ; 
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  codestring (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_indexed (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ singlevaraux (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * str_checkname (TYPE_2__*) ; 

__attribute__((used)) static void singlevar (LexState *ls, expdesc *var) {
  TString *varname = str_checkname(ls);
  FuncState *fs = ls->fs;
  if (singlevaraux(fs, varname, var, 1) == VVOID) {  /* global name? */
    expdesc key;
    singlevaraux(fs, ls->envn, var, 1);  /* get environment variable */
    lua_assert(var->k == VLOCAL || var->k == VUPVAL);
    codestring(ls, &key, varname);  /* key is variable name */
    luaK_indexed(fs, var, &key);  /* env[varname] */
  }
}