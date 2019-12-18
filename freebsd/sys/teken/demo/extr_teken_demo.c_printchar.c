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
struct TYPE_5__ {size_t tp_row; size_t tp_col; } ;
typedef  TYPE_2__ teken_pos_t ;
struct TYPE_4__ {int ta_format; int /*<<< orphan*/  ta_bgcolor; int /*<<< orphan*/  ta_fgcolor; } ;
struct pixel {int c; TYPE_1__ a; } ;

/* Variables and functions */
 int A_BLINK ; 
 int A_BOLD ; 
 int A_REVERSE ; 
 int A_UNDERLINE ; 
 int COLOR_PAIR (int) ; 
 size_t NCOLS ; 
 size_t NROWS ; 
 int TF_BLINK ; 
 int TF_BOLD ; 
 int TF_CJK_RIGHT ; 
 int TF_REVERSE ; 
 int TF_UNDERLINE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bkgdset (int) ; 
 struct pixel** buffer ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  move (int,int) ; 
 int /*<<< orphan*/  mvaddstr (size_t,size_t,char*) ; 
 int /*<<< orphan*/  stdscr ; 
 int teken_256to8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
printchar(const teken_pos_t *p)
{
	int y, x, attr = 0;
	struct pixel *px;
	char str[5] = { 0 };

	assert(p->tp_row < NROWS);
	assert(p->tp_col < NCOLS);

	px = &buffer[p->tp_col][p->tp_row];
	/* No need to print right hand side of CJK character manually. */
	if (px->a.ta_format & TF_CJK_RIGHT)
		return;

	/* Convert Unicode to UTF-8. */
	if (px->c < 0x80) {
		str[0] = px->c;
	} else if (px->c < 0x800) {
		str[0] = 0xc0 | (px->c >> 6);
		str[1] = 0x80 | (px->c & 0x3f);
	} else if (px->c < 0x10000) {
		str[0] = 0xe0 | (px->c >> 12);
		str[1] = 0x80 | ((px->c >> 6) & 0x3f);
		str[2] = 0x80 | (px->c & 0x3f);
	} else {
		str[0] = 0xf0 | (px->c >> 18);
		str[1] = 0x80 | ((px->c >> 12) & 0x3f);
		str[2] = 0x80 | ((px->c >> 6) & 0x3f);
		str[3] = 0x80 | (px->c & 0x3f);
	}

	if (px->a.ta_format & TF_BOLD)
		attr |= A_BOLD;
	if (px->a.ta_format & TF_UNDERLINE)
		attr |= A_UNDERLINE;
	if (px->a.ta_format & TF_BLINK)
		attr |= A_BLINK;
	if (px->a.ta_format & TF_REVERSE)
		attr |= A_REVERSE;

	bkgdset(attr | COLOR_PAIR(teken_256to8(px->a.ta_fgcolor) +
	      8 * teken_256to8(px->a.ta_bgcolor)));
	getyx(stdscr, y, x);
	mvaddstr(p->tp_row, p->tp_col, str);
	move(y, x);
}