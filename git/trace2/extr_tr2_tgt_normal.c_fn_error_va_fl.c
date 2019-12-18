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
 int /*<<< orphan*/  maybe_append_string_va (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normal_io_write_fl (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_error_va_fl(const char *file, int line, const char *fmt,
			   va_list ap)
{
	struct strbuf buf_payload = STRBUF_INIT;

	strbuf_addstr(&buf_payload, "error");
	if (fmt && *fmt) {
		strbuf_addch(&buf_payload, ' ');
		maybe_append_string_va(&buf_payload, fmt, ap);
	}
	normal_io_write_fl(file, line, &buf_payload);
	strbuf_release(&buf_payload);
}