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
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void append_quoted_string(struct strbuf *out, const char *in)
{
	unsigned char c;

	strbuf_addch(out, '"');
	while ((c = *in++) != '\0') {
		if (c == '"')
			strbuf_addstr(out, "\\\"");
		else if (c == '\\')
			strbuf_addstr(out, "\\\\");
		else if (c == '\n')
			strbuf_addstr(out, "\\n");
		else if (c == '\r')
			strbuf_addstr(out, "\\r");
		else if (c == '\t')
			strbuf_addstr(out, "\\t");
		else if (c == '\f')
			strbuf_addstr(out, "\\f");
		else if (c == '\b')
			strbuf_addstr(out, "\\b");
		else if (c < 0x20)
			strbuf_addf(out, "\\u%04x", c);
		else
			strbuf_addch(out, c);
	}
	strbuf_addch(out, '"');
}