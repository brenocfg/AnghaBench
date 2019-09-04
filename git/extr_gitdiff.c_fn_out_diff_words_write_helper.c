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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct diff_words_style_elem {char const* color; char const* prefix; char const* suffix; } ;
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_WORD_DIFF ; 
 char* GIT_COLOR_RESET ; 
 struct strbuf STRBUF_INIT ; 
 char const* diff_line_prefix (struct diff_options*) ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int fn_out_diff_words_write_helper(struct diff_options *o,
					  struct diff_words_style_elem *st_el,
					  const char *newline,
					  size_t count, const char *buf)
{
	int print = 0;
	struct strbuf sb = STRBUF_INIT;

	while (count) {
		char *p = memchr(buf, '\n', count);
		if (print)
			strbuf_addstr(&sb, diff_line_prefix(o));

		if (p != buf) {
			const char *reset = st_el->color && *st_el->color ?
					    GIT_COLOR_RESET : NULL;
			if (st_el->color && *st_el->color)
				strbuf_addstr(&sb, st_el->color);
			strbuf_addstr(&sb, st_el->prefix);
			strbuf_add(&sb, buf, p ? p - buf : count);
			strbuf_addstr(&sb, st_el->suffix);
			if (reset)
				strbuf_addstr(&sb, reset);
		}
		if (!p)
			goto out;

		strbuf_addstr(&sb, newline);
		count -= p + 1 - buf;
		buf = p + 1;
		print = 1;
		if (count) {
			emit_diff_symbol(o, DIFF_SYMBOL_WORD_DIFF,
					 sb.buf, sb.len, 0);
			strbuf_reset(&sb);
		}
	}

out:
	if (sb.len)
		emit_diff_symbol(o, DIFF_SYMBOL_WORD_DIFF,
				 sb.buf, sb.len, 0);
	strbuf_release(&sb);
	return 0;
}