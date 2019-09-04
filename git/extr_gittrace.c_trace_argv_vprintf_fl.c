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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  prepare_trace_line (char const*,int,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  print_trace_line (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  sq_quote_argv_pretty (struct strbuf*,char const**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_vaddf (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_default_key ; 

__attribute__((used)) static void trace_argv_vprintf_fl(const char *file, int line,
				  const char **argv, const char *format,
				  va_list ap)
{
	struct strbuf buf = STRBUF_INIT;

	if (!prepare_trace_line(file, line, &trace_default_key, &buf))
		return;

	strbuf_vaddf(&buf, format, ap);

	sq_quote_argv_pretty(&buf, argv);
	print_trace_line(&trace_default_key, &buf);
	strbuf_release(&buf);
}