#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  l_noret ;
struct TYPE_5__ {scalar_t__ token; } ;
struct TYPE_6__ {TYPE_1__ t; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_2__*,char const*) ; 

__attribute__((used)) static l_noret semerror (LexState *ls, const char *msg) {
  ls->t.token = 0;  /* remove 'near to' from final message */
  luaX_syntaxerror(ls, msg);
}