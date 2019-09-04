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
struct child_process {char const* trace2_hook_name; char* trace2_child_class; char const* dir; int /*<<< orphan*/  argv; scalar_t__ git_cmd; int /*<<< orphan*/  use_shell; int /*<<< orphan*/  trace2_child_id; } ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  event_fmt_prepare (char const*,char const*,int,int /*<<< orphan*/ *,struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_argv (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_array_string (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_bool (struct json_writer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_inline_begin_array (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_object_intmax (struct json_writer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,char const*) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  tr2_dst_write_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_event ; 

__attribute__((used)) static void fn_child_start_fl(const char *file, int line,
			      uint64_t us_elapsed_absolute,
			      const struct child_process *cmd)
{
	const char *event_name = "child_start";
	struct json_writer jw = JSON_WRITER_INIT;

	jw_object_begin(&jw, 0);
	event_fmt_prepare(event_name, file, line, NULL, &jw);
	jw_object_intmax(&jw, "child_id", cmd->trace2_child_id);
	if (cmd->trace2_hook_name) {
		jw_object_string(&jw, "child_class", "hook");
		jw_object_string(&jw, "hook_name", cmd->trace2_hook_name);
	} else {
		const char *child_class =
			cmd->trace2_child_class ? cmd->trace2_child_class : "?";
		jw_object_string(&jw, "child_class", child_class);
	}
	if (cmd->dir)
		jw_object_string(&jw, "cd", cmd->dir);
	jw_object_bool(&jw, "use_shell", cmd->use_shell);
	jw_object_inline_begin_array(&jw, "argv");
	if (cmd->git_cmd)
		jw_array_string(&jw, "git");
	jw_array_argv(&jw, cmd->argv);
	jw_end(&jw);
	jw_end(&jw);

	tr2_dst_write_line(&tr2dst_event, &jw.json);
	jw_release(&jw);
}