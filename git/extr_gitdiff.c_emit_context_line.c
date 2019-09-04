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
 int /*<<< orphan*/  DIFF_SYMBOL_CONTEXT ; 
 unsigned int WSEH_CONTEXT ; 
 int /*<<< orphan*/  emit_diff_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,unsigned int) ; 

__attribute__((used)) static void emit_context_line(struct emit_callback *ecbdata,
			      const char *line, int len)
{
	unsigned flags = WSEH_CONTEXT | ecbdata->ws_rule;
	emit_diff_symbol(ecbdata->opt, DIFF_SYMBOL_CONTEXT, line, len, flags);
}