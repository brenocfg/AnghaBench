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
struct trace_key {int dummy; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  prepare_trace_line (char const*,int,struct trace_key*,struct strbuf*) ; 
 int /*<<< orphan*/  print_trace_line (struct trace_key*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_vaddf (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trace_vprintf_fl(const char *file, int line, struct trace_key *key,
			     const char *format, va_list ap)
{
	struct strbuf buf = STRBUF_INIT;

	if (!prepare_trace_line(file, line, key, &buf))
		return;

	strbuf_vaddf(&buf, format, ap);
	print_trace_line(key, &buf);
	strbuf_release(&buf);
}