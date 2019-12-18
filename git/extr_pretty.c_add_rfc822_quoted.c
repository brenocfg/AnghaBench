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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 

__attribute__((used)) static void add_rfc822_quoted(struct strbuf *out, const char *s, int len)
{
	int i;

	/* just a guess, we may have to also backslash-quote */
	strbuf_grow(out, len + 2);

	strbuf_addch(out, '"');
	for (i = 0; i < len; i++) {
		switch (s[i]) {
		case '"':
		case '\\':
			strbuf_addch(out, '\\');
			/* fall through */
		default:
			strbuf_addch(out, s[i]);
		}
	}
	strbuf_addch(out, '"');
}