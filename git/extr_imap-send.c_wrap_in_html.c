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
struct strbuf {char const* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr_xml_quoted (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void wrap_in_html(struct strbuf *msg)
{
	struct strbuf buf = STRBUF_INIT;
	static char *content_type = "Content-Type: text/html;\n";
	static char *pre_open = "<pre>\n";
	static char *pre_close = "</pre>\n";
	const char *body = strstr(msg->buf, "\n\n");

	if (!body)
		return; /* Headers but no body; no wrapping needed */

	body += 2;

	strbuf_add(&buf, msg->buf, body - msg->buf - 1);
	strbuf_addstr(&buf, content_type);
	strbuf_addch(&buf, '\n');
	strbuf_addstr(&buf, pre_open);
	strbuf_addstr_xml_quoted(&buf, body);
	strbuf_addstr(&buf, pre_close);

	strbuf_release(msg);
	*msg = buf;
}