#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct transport {struct helper_data* data; } ;
struct string_list {int nr; TYPE_1__* items; } ;
struct helper_data {scalar_t__ import_marks; scalar_t__ export_marks; scalar_t__ signed_tags; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  child_process_init (struct child_process*) ; 
 int /*<<< orphan*/  dup (int /*<<< orphan*/ ) ; 
 struct child_process* get_helper (struct transport*) ; 
 int start_command (struct child_process*) ; 

__attribute__((used)) static int get_exporter(struct transport *transport,
			struct child_process *fastexport,
			struct string_list *revlist_args)
{
	struct helper_data *data = transport->data;
	struct child_process *helper = get_helper(transport);
	int i;

	child_process_init(fastexport);

	/* we need to duplicate helper->in because we want to use it after
	 * fastexport is done with it. */
	fastexport->out = dup(helper->in);
	argv_array_push(&fastexport->args, "fast-export");
	argv_array_push(&fastexport->args, "--use-done-feature");
	argv_array_push(&fastexport->args, data->signed_tags ?
		"--signed-tags=verbatim" : "--signed-tags=warn-strip");
	if (data->export_marks)
		argv_array_pushf(&fastexport->args, "--export-marks=%s.tmp", data->export_marks);
	if (data->import_marks)
		argv_array_pushf(&fastexport->args, "--import-marks=%s", data->import_marks);

	for (i = 0; i < revlist_args->nr; i++)
		argv_array_push(&fastexport->args, revlist_args->items[i].string);

	fastexport->git_cmd = 1;
	return start_command(fastexport);
}