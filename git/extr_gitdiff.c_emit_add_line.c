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
struct emit_callback {unsigned int ws_rule; int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 unsigned int DIFF_SYMBOL_CONTENT_BLANK_LINE_EOF ; 
 int /*<<< orphan*/  DIFF_SYMBOL_PLUS ; 
 unsigned int WSEH_NEW ; 
 int /*<<< orphan*/  emit_diff_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,unsigned int) ; 
 scalar_t__ new_blank_line_at_eof (struct emit_callback*,char const*,int) ; 

__attribute__((used)) static void emit_add_line(struct emit_callback *ecbdata,
			  const char *line, int len)
{
	unsigned flags = WSEH_NEW | ecbdata->ws_rule;
	if (new_blank_line_at_eof(ecbdata, line, len))
		flags |= DIFF_SYMBOL_CONTENT_BLANK_LINE_EOF;

	emit_diff_symbol(ecbdata->opt, DIFF_SYMBOL_PLUS, line, len, flags);
}