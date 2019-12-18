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
struct TYPE_3__ {int /*<<< orphan*/  atr; } ;
struct TYPE_4__ {TYPE_1__ title; } ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ dlg ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  mvwaddnstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void print_title(WINDOW *dialog, const char *title, int width)
{
	if (title) {
		int tlen = MIN(width - 2, strlen(title));
		wattrset(dialog, dlg.title.atr);
		mvwaddch(dialog, 0, (width - tlen) / 2 - 1, ' ');
		mvwaddnstr(dialog, 0, (width - tlen)/2, title, tlen);
		waddch(dialog, ' ');
	}
}