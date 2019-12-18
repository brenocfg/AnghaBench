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
struct grep_opt {scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  compile_grep_patterns_real (struct grep_opt*) ; 
 int /*<<< orphan*/  dump_grep_expression (struct grep_opt*) ; 

void compile_grep_patterns(struct grep_opt *opt)
{
	compile_grep_patterns_real(opt);
	if (opt->debug)
		dump_grep_expression(opt);
}