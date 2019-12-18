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

/* Variables and functions */
 int TRACE_QUOTE ; 
 int /*<<< orphan*/  dump_buffer (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* lquote ; 
 char* rquote ; 
 int trace_flags ; 
 int /*<<< orphan*/  traceout ; 

void
finish_trace(size_t mark)
{
	fprintf(traceout, " -> ");
	if (trace_flags & TRACE_QUOTE)
		fprintf(traceout, "%s", lquote);
	dump_buffer(traceout, mark);
	if (trace_flags & TRACE_QUOTE)
		fprintf(traceout, "%s", rquote);
	fprintf(traceout, "\n");
}