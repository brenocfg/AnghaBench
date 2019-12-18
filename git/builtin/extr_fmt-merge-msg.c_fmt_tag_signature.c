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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void fmt_tag_signature(struct strbuf *tagbuf,
			      struct strbuf *sig,
			      const char *buf,
			      unsigned long len)
{
	const char *tag_body = strstr(buf, "\n\n");
	if (tag_body) {
		tag_body += 2;
		strbuf_add(tagbuf, tag_body, buf + len - tag_body);
	}
	strbuf_complete_line(tagbuf);
	if (sig->len) {
		strbuf_addch(tagbuf, '\n');
		strbuf_add_commented_lines(tagbuf, sig->buf, sig->len);
	}
}