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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 char* unquote_comment (struct strbuf*,char const*) ; 
 char* unquote_quoted_string (struct strbuf*,char const*) ; 

__attribute__((used)) static void unquote_quoted_pair(struct strbuf *line)
{
	struct strbuf outbuf;
	const char *in = line->buf;
	int c;

	strbuf_init(&outbuf, line->len);

	while ((c = *in++) != 0) {
		switch (c) {
		case '"':
			in = unquote_quoted_string(&outbuf, in);
			continue;
		case '(':
			in = unquote_comment(&outbuf, in);
			continue;
		}

		strbuf_addch(&outbuf, c);
	}

	strbuf_swap(&outbuf, line);
	strbuf_release(&outbuf);

}