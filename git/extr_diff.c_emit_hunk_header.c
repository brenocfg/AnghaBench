#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char const* buf; int len; } ;
struct emit_callback {TYPE_2__* opt; scalar_t__ color_diff; } ;
typedef  int /*<<< orphan*/  atat ;
struct TYPE_3__ {scalar_t__ suppress_hunk_header_line_count; scalar_t__ dual_color_diffed_diffs; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_CONTEXT ; 
 int /*<<< orphan*/  DIFF_FRAGINFO ; 
 int /*<<< orphan*/  DIFF_FUNCINFO ; 
 int /*<<< orphan*/  DIFF_RESET ; 
 int /*<<< orphan*/  DIFF_SYMBOL_CONTEXT_FRAGINFO ; 
 int /*<<< orphan*/  DIFF_SYMBOL_CONTEXT_MARKER ; 
 char* GIT_COLOR_REVERSE ; 
 struct strbuf STRBUF_INIT ; 
 char* diff_get_color (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_diff_symbol (TYPE_2__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 char* memmem (char const*,int,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void emit_hunk_header(struct emit_callback *ecbdata,
			     const char *line, int len)
{
	const char *context = diff_get_color(ecbdata->color_diff, DIFF_CONTEXT);
	const char *frag = diff_get_color(ecbdata->color_diff, DIFF_FRAGINFO);
	const char *func = diff_get_color(ecbdata->color_diff, DIFF_FUNCINFO);
	const char *reset = diff_get_color(ecbdata->color_diff, DIFF_RESET);
	const char *reverse = ecbdata->color_diff ? GIT_COLOR_REVERSE : "";
	static const char atat[2] = { '@', '@' };
	const char *cp, *ep;
	struct strbuf msgbuf = STRBUF_INIT;
	int org_len = len;
	int i = 1;

	/*
	 * As a hunk header must begin with "@@ -<old>, +<new> @@",
	 * it always is at least 10 bytes long.
	 */
	if (len < 10 ||
	    memcmp(line, atat, 2) ||
	    !(ep = memmem(line + 2, len - 2, atat, 2))) {
		emit_diff_symbol(ecbdata->opt,
				 DIFF_SYMBOL_CONTEXT_MARKER, line, len, 0);
		return;
	}
	ep += 2; /* skip over @@ */

	/* The hunk header in fraginfo color */
	if (ecbdata->opt->flags.dual_color_diffed_diffs)
		strbuf_addstr(&msgbuf, reverse);
	strbuf_addstr(&msgbuf, frag);
	if (ecbdata->opt->flags.suppress_hunk_header_line_count)
		strbuf_add(&msgbuf, atat, sizeof(atat));
	else
		strbuf_add(&msgbuf, line, ep - line);
	strbuf_addstr(&msgbuf, reset);

	/*
	 * trailing "\r\n"
	 */
	for ( ; i < 3; i++)
		if (line[len - i] == '\r' || line[len - i] == '\n')
			len--;

	/* blank before the func header */
	for (cp = ep; ep - line < len; ep++)
		if (*ep != ' ' && *ep != '\t')
			break;
	if (ep != cp) {
		strbuf_addstr(&msgbuf, context);
		strbuf_add(&msgbuf, cp, ep - cp);
		strbuf_addstr(&msgbuf, reset);
	}

	if (ep < line + len) {
		strbuf_addstr(&msgbuf, func);
		strbuf_add(&msgbuf, ep, line + len - ep);
		strbuf_addstr(&msgbuf, reset);
	}

	strbuf_add(&msgbuf, line + len, org_len - len);
	strbuf_complete_line(&msgbuf);
	emit_diff_symbol(ecbdata->opt,
			 DIFF_SYMBOL_CONTEXT_FRAGINFO, msgbuf.buf, msgbuf.len, 0);
	strbuf_release(&msgbuf);
}