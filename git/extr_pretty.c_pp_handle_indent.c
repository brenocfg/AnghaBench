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
struct pretty_print_context {scalar_t__ expand_tabs_in_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add_tabexpand (struct strbuf*,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 

__attribute__((used)) static void pp_handle_indent(struct pretty_print_context *pp,
			     struct strbuf *sb, int indent,
			     const char *line, int linelen)
{
	strbuf_addchars(sb, ' ', indent);
	if (pp->expand_tabs_in_log)
		strbuf_add_tabexpand(sb, pp->expand_tabs_in_log, line, linelen);
	else
		strbuf_add(sb, line, linelen);
}