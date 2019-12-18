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
struct json_writer {int /*<<< orphan*/  json; } ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  event_fmt_prepare (char const*,char const*,int,int /*<<< orphan*/ *,struct json_writer*) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,char const*) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  maybe_add_string_va (struct json_writer*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_event ; 

__attribute__((used)) static void fn_error_va_fl(const char *file, int line, const char *fmt,
			   va_list ap)
{
	const char *event_name = "error";
	struct json_writer jw = JSON_WRITER_INIT;

	jw_object_begin(&jw, 0);
	event_fmt_prepare(event_name, file, line, NULL, &jw);
	maybe_add_string_va(&jw, "msg", fmt, ap);
	/*
	 * Also emit the format string as a field in case
	 * post-processors want to aggregate common error
	 * messages by type without argument fields (such
	 * as pathnames or branch names) cluttering it up.
	 */
	if (fmt && *fmt)
		jw_object_string(&jw, "fmt", fmt);
	jw_end(&jw);

	tr2_dst_write_line(&tr2dst_event, &jw.json);
	jw_release(&jw);
}