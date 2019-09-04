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
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__ uint64_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  perf_indent ; 
 int /*<<< orphan*/  prepare_trace_line (char const*,int,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  print_trace_line (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,double,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_vaddf (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  trace_perf_key ; 

__attribute__((used)) static void trace_performance_vprintf_fl(const char *file, int line,
					 uint64_t nanos, const char *format,
					 va_list ap)
{
	static const char space[] = "          ";
	struct strbuf buf = STRBUF_INIT;

	if (!prepare_trace_line(file, line, &trace_perf_key, &buf))
		return;

	strbuf_addf(&buf, "performance: %.9f s", (double) nanos / 1000000000);

	if (format && *format) {
		if (perf_indent >= strlen(space))
			BUG("Too deep indentation");

		strbuf_addf(&buf, ":%.*s ", perf_indent, space);
		strbuf_vaddf(&buf, format, ap);
	}

	print_trace_line(&trace_perf_key, &buf);
	strbuf_release(&buf);
}