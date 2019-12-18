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
struct input_file {int dummy; } ;

/* Variables and functions */
 char COMMA ; 
 char EOS ; 
 char LPAREN ; 
 int RPAREN ; 
 size_t SIZE_MAX ; 
 int TRACE_ARGS ; 
 int TRACE_CONT ; 
 int TRACE_EXPANSION ; 
 int TRACE_QUOTE ; 
 size_t buffer_mark () ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 char* lquote ; 
 int /*<<< orphan*/  print_header (struct input_file*) ; 
 char* rquote ; 
 scalar_t__ stderr ; 
 int trace_flags ; 
 scalar_t__ traceout ; 

size_t
trace(const char *argv[], int argc, struct input_file *inp)
{
	if (!traceout)
		traceout = stderr;
	print_header(inp);
	if (trace_flags & TRACE_CONT) {
		fprintf(traceout, "%s ...\n", argv[1]);
		print_header(inp);
	}
	fprintf(traceout, "%s", argv[1]);
	if ((trace_flags & TRACE_ARGS) && argc > 2) {
		char delim[3];
		int i;

		delim[0] = LPAREN;
		delim[1] = EOS;
		for (i = 2; i < argc; i++) {
			fprintf(traceout, "%s%s%s%s", delim,
			    (trace_flags & TRACE_QUOTE) ? lquote : "",
			    argv[i],
			    (trace_flags & TRACE_QUOTE) ? rquote : "");
			delim[0] = COMMA;
			delim[1] = ' ';
			delim[2] = EOS;
		}
		fprintf(traceout, "%c", RPAREN);
	}
	if (trace_flags & TRACE_CONT) {
		fprintf(traceout, " -> ???\n");
		print_header(inp);
		fprintf(traceout, argc > 2 ? "%s(...)" : "%s", argv[1]);
	}
	if (trace_flags & TRACE_EXPANSION)
		return buffer_mark();
	else {
		fprintf(traceout, "\n");
		return SIZE_MAX;
	}
}