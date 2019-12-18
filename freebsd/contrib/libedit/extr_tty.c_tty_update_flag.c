#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tcflag_t ;
struct TYPE_6__ {TYPE_1__** t_t; } ;
struct TYPE_7__ {TYPE_2__ el_tty; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_setmask; int /*<<< orphan*/  t_clrmask; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */

__attribute__((used)) static tcflag_t
tty_update_flag(EditLine *el, tcflag_t f, int mode, int kind)
{
	f &= ~el->el_tty.t_t[mode][kind].t_clrmask;
	f |= el->el_tty.t_t[mode][kind].t_setmask;
	return f;
}