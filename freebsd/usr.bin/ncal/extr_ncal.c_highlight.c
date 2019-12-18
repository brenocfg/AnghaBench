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

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ flag_nohighlight ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int tgetent (char*,int /*<<< orphan*/ *) ; 
 char* tgetstr (char*,char**) ; 

__attribute__((used)) static void
highlight(char *dst, char *src, int len, int *extralen)
{
	static int first = 1;
	static const char *term_so, *term_se;

	if (first) {
		static char cbuf[512];
		char tbuf[1024], *b;

		term_se = term_so = NULL;

		/* On how to highlight on this type of terminal (if any). */
		if (isatty(STDOUT_FILENO) && tgetent(tbuf, NULL) == 1) {
			b = cbuf;
			term_so = tgetstr("so", &b);
			term_se = tgetstr("se", &b);
		}

		first = 0;
	}

	/*
	 * This check is not necessary, should have been handled before calling
	 * this function.
	 */
	if (flag_nohighlight) {
		memcpy(dst, src, len);
		return;
	}

	/*
	 * If it is a real terminal, use the data from the termcap database.
	 */
	if (term_so != NULL && term_se != NULL) {
		/* separator. */
		dst[0] = ' ';
		dst++;
		/* highlight on. */
		memcpy(dst, term_so, strlen(term_so));
		dst += strlen(term_so);
		/* the actual text. (minus leading space) */
		len--;
		src++;
		memcpy(dst, src, len);
		dst += len;
		/* highlight off. */
		memcpy(dst, term_se, strlen(term_se));
		*extralen = strlen(term_so) + strlen(term_se);
		return;
	}

	/*
	 * Otherwise, print a _, backspace and the letter.
	 */
	*extralen = 0;
	/* skip leading space. */
	src++;
	len--;
	/* separator. */
	dst[0] = ' ';
	dst++;
	while (len > 0) {
		/* _ and backspace. */
		memcpy(dst, "_\010", 2);
		dst += 2;
		*extralen += 2;
		/* the character. */
		*dst++ = *src++;
		len--;
	}
	return;
}