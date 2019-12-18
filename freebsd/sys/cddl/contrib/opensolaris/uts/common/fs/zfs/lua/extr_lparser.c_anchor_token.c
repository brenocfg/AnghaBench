#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* ts; } ;
struct TYPE_11__ {scalar_t__ token; TYPE_2__ seminfo; } ;
struct TYPE_13__ {TYPE_3__ t; int /*<<< orphan*/ * fs; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; } ;
struct TYPE_12__ {TYPE_1__ tsv; } ;
typedef  TYPE_4__ TString ;
typedef  TYPE_5__ LexState ;

/* Variables and functions */
 scalar_t__ TK_EOS ; 
 scalar_t__ TK_NAME ; 
 scalar_t__ TK_STRING ; 
 int /*<<< orphan*/  getstr (TYPE_4__*) ; 
 int /*<<< orphan*/  luaX_newstring (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void anchor_token (LexState *ls) {
  /* last token from outer function must be EOS */
  lua_assert(ls->fs != NULL || ls->t.token == TK_EOS);
  if (ls->t.token == TK_NAME || ls->t.token == TK_STRING) {
    TString *ts = ls->t.seminfo.ts;
    luaX_newstring(ls, getstr(ts), ts->tsv.len);
  }
}