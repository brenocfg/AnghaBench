#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {int /*<<< orphan*/  atr; } ;
struct TYPE_4__ {int /*<<< orphan*/  atr; } ;
struct TYPE_6__ {TYPE_2__ dialog; TYPE_1__ border; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  ACS_LTEE ; 
 int /*<<< orphan*/  ACS_RTEE ; 
 int ERRDISPLAYTOOSMALL ; 
#define  KEY_ESC 132 
#define  KEY_LEFT 131 
#define  KEY_RESIZE 130 
#define  KEY_RIGHT 129 
#define  TAB 128 
 int /*<<< orphan*/  TRUE ; 
 int YESNO_HEIGTH_MIN ; 
 int YESNO_WIDTH_MIN ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 TYPE_3__ dlg ; 
 int /*<<< orphan*/  draw_box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_shadow (int /*<<< orphan*/ ,int,int,int,int) ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int on_key_esc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_key_resize () ; 
 int /*<<< orphan*/  print_autowrap (int /*<<< orphan*/ *,char const*,int,int,int) ; 
 int /*<<< orphan*/  print_buttons (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  print_title (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wgetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

int dialog_yesno(const char *title, const char *prompt, int height, int width)
{
	int i, x, y, key = 0, button = 0;
	WINDOW *dialog;

do_resize:
	if (getmaxy(stdscr) < (height + YESNO_HEIGTH_MIN))
		return -ERRDISPLAYTOOSMALL;
	if (getmaxx(stdscr) < (width + YESNO_WIDTH_MIN))
		return -ERRDISPLAYTOOSMALL;

	/* center dialog box on screen */
	x = (getmaxx(stdscr) - width) / 2;
	y = (getmaxy(stdscr) - height) / 2;

	draw_shadow(stdscr, y, x, height, width);

	dialog = newwin(height, width, y, x);
	keypad(dialog, TRUE);

	draw_box(dialog, 0, 0, height, width,
		 dlg.dialog.atr, dlg.border.atr);
	wattrset(dialog, dlg.border.atr);
	mvwaddch(dialog, height - 3, 0, ACS_LTEE);
	for (i = 0; i < width - 2; i++)
		waddch(dialog, ACS_HLINE);
	wattrset(dialog, dlg.dialog.atr);
	waddch(dialog, ACS_RTEE);

	print_title(dialog, title, width);

	wattrset(dialog, dlg.dialog.atr);
	print_autowrap(dialog, prompt, width - 2, 1, 3);

	print_buttons(dialog, height, width, 0);

	while (key != KEY_ESC) {
		key = wgetch(dialog);
		switch (key) {
		case 'Y':
		case 'y':
			delwin(dialog);
			return 0;
		case 'N':
		case 'n':
			delwin(dialog);
			return 1;

		case TAB:
		case KEY_LEFT:
		case KEY_RIGHT:
			button = ((key == KEY_LEFT ? --button : ++button) < 0) ? 1 : (button > 1 ? 0 : button);

			print_buttons(dialog, height, width, button);
			wrefresh(dialog);
			break;
		case ' ':
		case '\n':
			delwin(dialog);
			return button;
		case KEY_ESC:
			key = on_key_esc(dialog);
			break;
		case KEY_RESIZE:
			delwin(dialog);
			on_key_resize();
			goto do_resize;
		}
	}

	delwin(dialog);
	return key;		/* ESC pressed */
}