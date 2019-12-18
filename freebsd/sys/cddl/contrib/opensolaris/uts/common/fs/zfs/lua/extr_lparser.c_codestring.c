#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  VK ; 
 int /*<<< orphan*/  init_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_stringK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void codestring (LexState *ls, expdesc *e, TString *s) {
  init_exp(e, VK, luaK_stringK(ls->fs, s));
}