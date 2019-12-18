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
struct mailinfo {int /*<<< orphan*/  delsp; int /*<<< orphan*/  format_flowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_filter (struct mailinfo*,struct strbuf*) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,size_t) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void handle_filter_flowed(struct mailinfo *mi, struct strbuf *line,
				 struct strbuf *prev)
{
	size_t len = line->len;
	const char *rest;

	if (!mi->format_flowed) {
		handle_filter(mi, line);
		return;
	}

	if (line->buf[len - 1] == '\n') {
		len--;
		if (len && line->buf[len - 1] == '\r')
			len--;
	}

	/* Keep signature separator as-is. */
	if (skip_prefix(line->buf, "-- ", &rest) && rest - line->buf == len) {
		if (prev->len) {
			handle_filter(mi, prev);
			strbuf_reset(prev);
		}
		handle_filter(mi, line);
		return;
	}

	/* Unstuff space-stuffed line. */
	if (len && line->buf[0] == ' ') {
		strbuf_remove(line, 0, 1);
		len--;
	}

	/* Save flowed line for later, but without the soft line break. */
	if (len && line->buf[len - 1] == ' ') {
		strbuf_add(prev, line->buf, len - !!mi->delsp);
		return;
	}

	/* Prepend any previous partial lines */
	strbuf_insert(line, 0, prev->buf, prev->len);
	strbuf_reset(prev);

	handle_filter(mi, line);
}