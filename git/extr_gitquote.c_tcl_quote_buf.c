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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

void tcl_quote_buf(struct strbuf *sb, const char *src)
{
	char c;

	strbuf_addch(sb, '"');
	while ((c = *src++)) {
		switch (c) {
		case '[': case ']':
		case '{': case '}':
		case '$': case '\\': case '"':
			strbuf_addch(sb, '\\');
			/* fallthrough */
		default:
			strbuf_addch(sb, c);
			break;
		case '\f':
			strbuf_addstr(sb, "\\f");
			break;
		case '\r':
			strbuf_addstr(sb, "\\r");
			break;
		case '\n':
			strbuf_addstr(sb, "\\n");
			break;
		case '\t':
			strbuf_addstr(sb, "\\t");
			break;
		case '\v':
			strbuf_addstr(sb, "\\v");
			break;
		}
	}
	strbuf_addch(sb, '"');
}