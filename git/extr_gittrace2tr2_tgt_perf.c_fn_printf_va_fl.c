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
typedef  int /*<<< orphan*/  uint64_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  maybe_append_string_va (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_io_write_fl (char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_printf_va_fl(const char *file, int line,
			    uint64_t us_elapsed_absolute, const char *fmt,
			    va_list ap)
{
	const char *event_name = "printf";
	struct strbuf buf_payload = STRBUF_INIT;

	maybe_append_string_va(&buf_payload, fmt, ap);

	perf_io_write_fl(file, line, event_name, NULL, &us_elapsed_absolute,
			 NULL, NULL, &buf_payload);
	strbuf_release(&buf_payload);
}