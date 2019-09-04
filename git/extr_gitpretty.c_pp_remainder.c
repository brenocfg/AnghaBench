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
struct pretty_print_context {scalar_t__ fmt; scalar_t__ expand_tabs_in_log; } ;

/* Variables and functions */
 scalar_t__ CMIT_FMT_MBOXRD ; 
 scalar_t__ CMIT_FMT_SHORT ; 
 int get_one_line (char const*) ; 
 scalar_t__ is_blank_line (char const*,int*) ; 
 scalar_t__ is_mboxrd_from (char const*,int) ; 
 int /*<<< orphan*/  pp_handle_indent (struct pretty_print_context*,struct strbuf*,int,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add_tabexpand (struct strbuf*,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 

void pp_remainder(struct pretty_print_context *pp,
		  const char **msg_p,
		  struct strbuf *sb,
		  int indent)
{
	int first = 1;
	for (;;) {
		const char *line = *msg_p;
		int linelen = get_one_line(line);
		*msg_p += linelen;

		if (!linelen)
			break;

		if (is_blank_line(line, &linelen)) {
			if (first)
				continue;
			if (pp->fmt == CMIT_FMT_SHORT)
				break;
		}
		first = 0;

		strbuf_grow(sb, linelen + indent + 20);
		if (indent)
			pp_handle_indent(pp, sb, indent, line, linelen);
		else if (pp->expand_tabs_in_log)
			strbuf_add_tabexpand(sb, pp->expand_tabs_in_log,
					     line, linelen);
		else {
			if (pp->fmt == CMIT_FMT_MBOXRD &&
					is_mboxrd_from(line, linelen))
				strbuf_addch(sb, '>');

			strbuf_add(sb, line, linelen);
		}
		strbuf_addch(sb, '\n');
	}
}