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
struct strbuf {size_t len; char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 

__attribute__((used)) static void unfold_value(struct strbuf *val)
{
	struct strbuf out = STRBUF_INIT;
	size_t i;

	strbuf_grow(&out, val->len);
	i = 0;
	while (i < val->len) {
		char c = val->buf[i++];
		if (c == '\n') {
			/* Collapse continuation down to a single space. */
			while (i < val->len && isspace(val->buf[i]))
				i++;
			strbuf_addch(&out, ' ');
		} else {
			strbuf_addch(&out, c);
		}
	}

	/* Empty lines may have left us with whitespace cruft at the edges */
	strbuf_trim(&out);

	/* output goes back to val as if we modified it in-place */
	strbuf_swap(&out, val);
	strbuf_release(&out);
}