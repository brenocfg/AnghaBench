#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_4__ {int /*<<< orphan*/  token; } ;
struct TYPE_5__ {char decpoint; int current; int linenumber; int lastline; int /*<<< orphan*/  buff; int /*<<< orphan*/ * L; int /*<<< orphan*/  envn; int /*<<< orphan*/ * source; int /*<<< orphan*/ * fs; int /*<<< orphan*/ * z; TYPE_1__ lookahead; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_ENV ; 
 int /*<<< orphan*/  LUA_MINBUFFER ; 
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  luaS_fix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_resizebuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luaX_setinput (lua_State *L, LexState *ls, ZIO *z, TString *source,
                    int firstchar) {
  ls->decpoint = '.';
  ls->L = L;
  ls->current = firstchar;
  ls->lookahead.token = TK_EOS;  /* no look-ahead token */
  ls->z = z;
  ls->fs = NULL;
  ls->linenumber = 1;
  ls->lastline = 1;
  ls->source = source;
  ls->envn = luaS_new(L, LUA_ENV);  /* create env name */
  luaS_fix(ls->envn);  /* never collect this name */
  luaZ_resizebuffer(ls->L, ls->buff, LUA_MINBUFFER);  /* initialize buffer */
}