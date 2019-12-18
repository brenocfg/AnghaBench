#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char wint_t ;
typedef  char wchar_t ;
struct TYPE_10__ {scalar_t__ h; int v; } ;
struct TYPE_11__ {TYPE_3__ t_size; } ;
struct TYPE_9__ {size_t r_oldcv; } ;
struct TYPE_8__ {scalar_t__ h; size_t v; } ;
struct TYPE_12__ {char** el_display; TYPE_4__ el_terminal; TYPE_2__ el_refresh; TYPE_1__ el_cursor; } ;
typedef  TYPE_5__ EditLine ;

/* Variables and functions */
 scalar_t__ EL_HAS_AUTO_MARGINS ; 
 scalar_t__ EL_HAS_MAGIC_MARGINS ; 
 char MB_FILL_CHAR ; 
 int /*<<< orphan*/  re__copy_and_pad (char*,char*,size_t) ; 
 int /*<<< orphan*/  terminal__putc (TYPE_5__*,char) ; 
 int wcwidth (char) ; 

__attribute__((used)) static void
re_fastputc(EditLine *el, wint_t c)
{
	wchar_t *lastline;
	int w;

	w = wcwidth(c);
	while (w > 1 && el->el_cursor.h + w > el->el_terminal.t_size.h)
	    re_fastputc(el, ' ');

	terminal__putc(el, c);
	el->el_display[el->el_cursor.v][el->el_cursor.h++] = c;
	while (--w > 0)
		el->el_display[el->el_cursor.v][el->el_cursor.h++]
			= MB_FILL_CHAR;

	if (el->el_cursor.h >= el->el_terminal.t_size.h) {
		/* if we must overflow */
		el->el_cursor.h = 0;

		/*
		 * If we would overflow (input is longer than terminal size),
		 * emulate scroll by dropping first line and shuffling the rest.
		 * We do this via pointer shuffling - it's safe in this case
		 * and we avoid memcpy().
		 */
		if (el->el_cursor.v + 1 >= el->el_terminal.t_size.v) {
			int i, lins = el->el_terminal.t_size.v;

			lastline = el->el_display[0];
			for(i = 1; i < lins; i++)
				el->el_display[i - 1] = el->el_display[i];

			el->el_display[i - 1] = lastline;
		} else {
			el->el_cursor.v++;
			lastline = el->el_display[++el->el_refresh.r_oldcv];
		}
		re__copy_and_pad(lastline, L"", (size_t)el->el_terminal.t_size.h);

		if (EL_HAS_AUTO_MARGINS) {
			if (EL_HAS_MAGIC_MARGINS) {
				terminal__putc(el, ' ');
				terminal__putc(el, '\b');
			}
		} else {
			terminal__putc(el, '\r');
			terminal__putc(el, '\n');
		}
	}
}