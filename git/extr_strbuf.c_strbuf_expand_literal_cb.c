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
 int hex2chr (char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 

size_t strbuf_expand_literal_cb(struct strbuf *sb,
				const char *placeholder,
				void *context)
{
	int ch;

	switch (placeholder[0]) {
	case 'n':		/* newline */
		strbuf_addch(sb, '\n');
		return 1;
	case 'x':
		/* %x00 == NUL, %x0a == LF, etc. */
		ch = hex2chr(placeholder + 1);
		if (ch < 0)
			return 0;
		strbuf_addch(sb, ch);
		return 3;
	}
	return 0;
}