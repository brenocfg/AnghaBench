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
typedef  char wint_t ;
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char WEOF ; 
 char* XMALLOC (size_t) ; 
 int /*<<< orphan*/  format_troff ; 
 char getwc (int /*<<< orphan*/ *) ; 
 scalar_t__ iswprint (char) ; 
 size_t tab_width ; 
 int wcwidth (char) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static wchar_t *
get_line(FILE *stream, size_t *lengthp)
{
	static wchar_t *buf = NULL;
	static size_t length = 0;
	size_t len = 0;
	wint_t ch;
	size_t spaces_pending = 0;
	int troff = 0;
	size_t col = 0;
	int cwidth;

	if (buf == NULL) {
		length = 100;
		buf = XMALLOC(length * sizeof(wchar_t));
	}
	while ((ch = getwc(stream)) != '\n' && ch != WEOF) {
		if (len + spaces_pending == 0 && ch == '.' && !format_troff)
			troff = 1;
		if (ch == ' ')
			++spaces_pending;
		else if (troff || iswprint(ch)) {
			while (len + spaces_pending >= length) {
				length *= 2;
				buf = xrealloc(buf, length * sizeof(wchar_t));
			}
			while (spaces_pending > 0) {
				--spaces_pending;
				buf[len++] = ' ';
				col++;
			}
			buf[len++] = ch;
			col += (cwidth = wcwidth(ch)) > 0 ? cwidth : 1;
		} else if (ch == '\t')
			spaces_pending += tab_width -
			    (col + spaces_pending) % tab_width;
		else if (ch == '\b') {
			if (len)
				--len;
			if (col)
				--col;
		}
	}
	*lengthp = len;
	return (len > 0 || ch != WEOF) ? buf : 0;
}