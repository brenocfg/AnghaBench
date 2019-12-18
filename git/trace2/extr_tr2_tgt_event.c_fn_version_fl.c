#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct json_writer {int /*<<< orphan*/  json; } ;
struct TYPE_3__ {scalar_t__ too_many_files; } ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  TR2_EVENT_VERSION ; 
 int /*<<< orphan*/  event_fmt_prepare (char const*,char const*,int,int /*<<< orphan*/ *,struct json_writer*) ; 
 int /*<<< orphan*/  fn_too_many_files_fl (char const*,int) ; 
 int /*<<< orphan*/  git_version_string ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  tr2_dst_write_line (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tr2dst_event ; 

__attribute__((used)) static void fn_version_fl(const char *file, int line)
{
	const char *event_name = "version";
	struct json_writer jw = JSON_WRITER_INIT;

	jw_object_begin(&jw, 0);
	event_fmt_prepare(event_name, file, line, NULL, &jw);
	jw_object_string(&jw, "evt", TR2_EVENT_VERSION);
	jw_object_string(&jw, "exe", git_version_string);
	jw_end(&jw);

	tr2_dst_write_line(&tr2dst_event, &jw.json);
	jw_release(&jw);

	if (tr2dst_event.too_many_files)
		fn_too_many_files_fl(file, line);
}