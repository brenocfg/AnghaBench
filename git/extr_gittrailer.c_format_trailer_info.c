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
struct trailer_info {size_t trailer_nr; char** trailers; scalar_t__ trailer_start; scalar_t__ trailer_end; } ;
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;
struct process_trailer_options {struct strbuf* separator; int /*<<< orphan*/  only_trailers; int /*<<< orphan*/  value_only; scalar_t__ unfold; int /*<<< orphan*/  filter_data; scalar_t__ (* filter ) (struct strbuf*,int /*<<< orphan*/ ) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int find_separator (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_trailer (struct strbuf*,struct strbuf*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  separators ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 scalar_t__ stub1 (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unfold_value (struct strbuf*) ; 

__attribute__((used)) static void format_trailer_info(struct strbuf *out,
				const struct trailer_info *info,
				const struct process_trailer_options *opts)
{
	size_t origlen = out->len;
	size_t i;

	/* If we want the whole block untouched, we can take the fast path. */
	if (!opts->only_trailers && !opts->unfold && !opts->filter && !opts->separator) {
		strbuf_add(out, info->trailer_start,
			   info->trailer_end - info->trailer_start);
		return;
	}

	for (i = 0; i < info->trailer_nr; i++) {
		char *trailer = info->trailers[i];
		ssize_t separator_pos = find_separator(trailer, separators);

		if (separator_pos >= 1) {
			struct strbuf tok = STRBUF_INIT;
			struct strbuf val = STRBUF_INIT;

			parse_trailer(&tok, &val, NULL, trailer, separator_pos);
			if (!opts->filter || opts->filter(&tok, opts->filter_data)) {
				if (opts->unfold)
					unfold_value(&val);

				if (opts->separator && out->len != origlen)
					strbuf_addbuf(out, opts->separator);
				if (!opts->value_only)
					strbuf_addf(out, "%s: ", tok.buf);
				strbuf_addbuf(out, &val);
				if (!opts->separator)
					strbuf_addch(out, '\n');
			}
			strbuf_release(&tok);
			strbuf_release(&val);

		} else if (!opts->only_trailers) {
			if (opts->separator && out->len != origlen) {
				strbuf_addbuf(out, opts->separator);
			}
			strbuf_addstr(out, trailer);
			if (opts->separator) {
				strbuf_rtrim(out);
			}
		}
	}

}