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
 char* memchr (char const*,char,unsigned long) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void append_lines(struct strbuf *out, const char *buf, unsigned long size, int lines)
{
	int i;
	const char *sp, *eol;
	size_t len;

	sp = buf;

	for (i = 0; i < lines && sp < buf + size; i++) {
		if (i)
			strbuf_addstr(out, "\n    ");
		eol = memchr(sp, '\n', size - (sp - buf));
		len = eol ? eol - sp : size - (sp - buf);
		strbuf_add(out, sp, len);
		if (!eol)
			break;
		sp = eol + 1;
	}
}