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
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 size_t strcspn (char const*,char*) ; 

void strbuf_addstr_xml_quoted(struct strbuf *buf, const char *s)
{
	while (*s) {
		size_t len = strcspn(s, "\"<>&");
		strbuf_add(buf, s, len);
		s += len;
		switch (*s) {
		case '"':
			strbuf_addstr(buf, "&quot;");
			break;
		case '<':
			strbuf_addstr(buf, "&lt;");
			break;
		case '>':
			strbuf_addstr(buf, "&gt;");
			break;
		case '&':
			strbuf_addstr(buf, "&amp;");
			break;
		case 0:
			return;
		}
		s++;
	}
}