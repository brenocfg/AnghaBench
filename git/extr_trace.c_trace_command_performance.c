#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 TYPE_1__ command_line ; 
 int /*<<< orphan*/  print_command_performance_atexit ; 
 int /*<<< orphan*/  sq_quote_argv_pretty (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_perf_key ; 
 int /*<<< orphan*/  trace_performance_enter () ; 
 int /*<<< orphan*/  trace_want (int /*<<< orphan*/ *) ; 

void trace_command_performance(const char **argv)
{
	if (!trace_want(&trace_perf_key))
		return;

	if (!command_line.len)
		atexit(print_command_performance_atexit);

	strbuf_reset(&command_line);
	sq_quote_argv_pretty(&command_line, argv);
	trace_performance_enter();
}