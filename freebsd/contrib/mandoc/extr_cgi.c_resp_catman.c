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
struct req {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  html_putchar (char) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
resp_catman(const struct req *req, const char *file)
{
	FILE		*f;
	char		*p;
	size_t		 sz;
	ssize_t		 len;
	int		 i;
	int		 italic, bold;

	if ((f = fopen(file, "r")) == NULL) {
		puts("<p>You specified an invalid manual file.</p>");
		return;
	}

	puts("<div class=\"catman\">\n"
	     "<pre>");

	p = NULL;
	sz = 0;

	while ((len = getline(&p, &sz, f)) != -1) {
		bold = italic = 0;
		for (i = 0; i < len - 1; i++) {
			/*
			 * This means that the catpage is out of state.
			 * Ignore it and keep going (although the
			 * catpage is bogus).
			 */

			if ('\b' == p[i] || '\n' == p[i])
				continue;

			/*
			 * Print a regular character.
			 * Close out any bold/italic scopes.
			 * If we're in back-space mode, make sure we'll
			 * have something to enter when we backspace.
			 */

			if ('\b' != p[i + 1]) {
				if (italic)
					printf("</i>");
				if (bold)
					printf("</b>");
				italic = bold = 0;
				html_putchar(p[i]);
				continue;
			} else if (i + 2 >= len)
				continue;

			/* Italic mode. */

			if ('_' == p[i]) {
				if (bold)
					printf("</b>");
				if ( ! italic)
					printf("<i>");
				bold = 0;
				italic = 1;
				i += 2;
				html_putchar(p[i]);
				continue;
			}

			/*
			 * Handle funny behaviour troff-isms.
			 * These grok'd from the original man2html.c.
			 */

			if (('+' == p[i] && 'o' == p[i + 2]) ||
					('o' == p[i] && '+' == p[i + 2]) ||
					('|' == p[i] && '=' == p[i + 2]) ||
					('=' == p[i] && '|' == p[i + 2]) ||
					('*' == p[i] && '=' == p[i + 2]) ||
					('=' == p[i] && '*' == p[i + 2]) ||
					('*' == p[i] && '|' == p[i + 2]) ||
					('|' == p[i] && '*' == p[i + 2]))  {
				if (italic)
					printf("</i>");
				if (bold)
					printf("</b>");
				italic = bold = 0;
				putchar('*');
				i += 2;
				continue;
			} else if (('|' == p[i] && '-' == p[i + 2]) ||
					('-' == p[i] && '|' == p[i + 1]) ||
					('+' == p[i] && '-' == p[i + 1]) ||
					('-' == p[i] && '+' == p[i + 1]) ||
					('+' == p[i] && '|' == p[i + 1]) ||
					('|' == p[i] && '+' == p[i + 1]))  {
				if (italic)
					printf("</i>");
				if (bold)
					printf("</b>");
				italic = bold = 0;
				putchar('+');
				i += 2;
				continue;
			}

			/* Bold mode. */

			if (italic)
				printf("</i>");
			if ( ! bold)
				printf("<b>");
			bold = 1;
			italic = 0;
			i += 2;
			html_putchar(p[i]);
		}

		/*
		 * Clean up the last character.
		 * We can get to a newline; don't print that.
		 */

		if (italic)
			printf("</i>");
		if (bold)
			printf("</b>");

		if (i == len - 1 && p[i] != '\n')
			html_putchar(p[i]);

		putchar('\n');
	}
	free(p);

	puts("</pre>\n"
	     "</div>");

	fclose(f);
}