#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int atr; } ;
struct TYPE_4__ {TYPE_1__ position_indicator; } ;

/* Variables and functions */
 int A_COLOR ; 
 int buf ; 
 TYPE_2__ dlg ; 
 scalar_t__ getmaxx (int /*<<< orphan*/ *) ; 
 scalar_t__ getmaxy (int /*<<< orphan*/ *) ; 
 int page ; 
 int strlen (int) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wbkgdset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void print_position(WINDOW * win)
{
	int percent;

	wattrset(win, dlg.position_indicator.atr);
	wbkgdset(win, dlg.position_indicator.atr & A_COLOR);
	percent = (page - buf) * 100 / strlen(buf);
	wmove(win, getmaxy(win) - 3, getmaxx(win) - 9);
	wprintw(win, "(%3d%%)", percent);
}