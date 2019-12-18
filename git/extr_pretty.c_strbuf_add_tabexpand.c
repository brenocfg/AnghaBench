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
struct strbuf {int dummy; } ;

/* Variables and functions */
 char* memchr (char const*,char,int) ; 
 int pp_utf8_width (char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 

__attribute__((used)) static void strbuf_add_tabexpand(struct strbuf *sb, int tabwidth,
				 const char *line, int linelen)
{
	const char *tab;

	while ((tab = memchr(line, '\t', linelen)) != NULL) {
		int width = pp_utf8_width(line, tab);

		/*
		 * If it wasn't well-formed utf8, or it
		 * had characters with badly defined
		 * width (control characters etc), just
		 * give up on trying to align things.
		 */
		if (width < 0)
			break;

		/* Output the data .. */
		strbuf_add(sb, line, tab - line);

		/* .. and the de-tabified tab */
		strbuf_addchars(sb, ' ', tabwidth - (width % tabwidth));

		/* Skip over the printed part .. */
		linelen -= tab + 1 - line;
		line = tab + 1;
	}

	/*
	 * Print out everything after the last tab without
	 * worrying about width - there's nothing more to
	 * align.
	 */
	strbuf_add(sb, line, linelen);
}