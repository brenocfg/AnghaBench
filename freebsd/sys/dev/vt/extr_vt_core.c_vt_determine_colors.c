#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  term_color_t ;
typedef  int /*<<< orphan*/  term_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCHAR_BGCOLOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCHAR_FGCOLOR (int /*<<< orphan*/ ) ; 
 int TCHAR_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCOLOR_LIGHT (int /*<<< orphan*/ ) ; 
 int TF_BLINK ; 
 int TF_BOLD ; 
 int TF_REVERSE ; 

void
vt_determine_colors(term_char_t c, int cursor,
    term_color_t *fg, term_color_t *bg)
{
	term_color_t tmp;
	int invert;

	invert = 0;

	*fg = TCHAR_FGCOLOR(c);
	if (TCHAR_FORMAT(c) & TF_BOLD)
		*fg = TCOLOR_LIGHT(*fg);
	*bg = TCHAR_BGCOLOR(c);
	if (TCHAR_FORMAT(c) & TF_BLINK)
		*bg = TCOLOR_LIGHT(*bg);

	if (TCHAR_FORMAT(c) & TF_REVERSE)
		invert ^= 1;
	if (cursor)
		invert ^= 1;

	if (invert) {
		tmp = *fg;
		*fg = *bg;
		*bg = tmp;
	}
}