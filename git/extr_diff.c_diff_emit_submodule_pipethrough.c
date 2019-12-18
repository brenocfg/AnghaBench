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
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_SUBMODULE_PIPETHROUGH ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

void diff_emit_submodule_pipethrough(struct diff_options *o,
				     const char *line, int len)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_PIPETHROUGH, line, len, 0);
}