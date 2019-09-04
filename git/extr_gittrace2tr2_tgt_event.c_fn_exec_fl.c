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
typedef  int /*<<< orphan*/  uint64_t ;
struct json_writer {int /*<<< orphan*/  json; } ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  event_fmt_prepare (char const*,char const*,int,int /*<<< orphan*/ *,struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_argv (struct json_writer*,char const**) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_inline_begin_array (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_object_intmax (struct json_writer*,char*,int) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,char const*) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_event ; 

__attribute__((used)) static void fn_exec_fl(const char *file, int line, uint64_t us_elapsed_absolute,
		       int exec_id, const char *exe, const char **argv)
{
	const char *event_name = "exec";
	struct json_writer jw = JSON_WRITER_INIT;

	jw_object_begin(&jw, 0);
	event_fmt_prepare(event_name, file, line, NULL, &jw);
	jw_object_intmax(&jw, "exec_id", exec_id);
	if (exe)
		jw_object_string(&jw, "exe", exe);
	jw_object_inline_begin_array(&jw, "argv");
	jw_array_argv(&jw, argv);
	jw_end(&jw);
	jw_end(&jw);

	tr2_dst_write_line(&tr2dst_event, &jw.json);
	jw_release(&jw);
}