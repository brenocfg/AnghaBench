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
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct child_process {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_2__ {struct child_process process; } ;
struct cmd2process {TYPE_1__ subprocess; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  handle_filter_error (struct strbuf*,struct cmd2process*,int /*<<< orphan*/ ) ; 
 int packet_flush_gently (int /*<<< orphan*/ ) ; 
 char* packet_read_line (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int packet_write_fmt_gently (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ subprocess_find_entry (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  subprocess_map ; 
 int /*<<< orphan*/  subprocess_map_initialized ; 
 int subprocess_read_status (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

int async_query_available_blobs(const char *cmd, struct string_list *available_paths)
{
	int err;
	char *line;
	struct cmd2process *entry;
	struct child_process *process;
	struct strbuf filter_status = STRBUF_INIT;

	assert(subprocess_map_initialized);
	entry = (struct cmd2process *)subprocess_find_entry(&subprocess_map, cmd);
	if (!entry) {
		error(_("external filter '%s' is not available anymore although "
			"not all paths have been filtered"), cmd);
		return 0;
	}
	process = &entry->subprocess.process;
	sigchain_push(SIGPIPE, SIG_IGN);

	err = packet_write_fmt_gently(
		process->in, "command=list_available_blobs\n");
	if (err)
		goto done;

	err = packet_flush_gently(process->in);
	if (err)
		goto done;

	while ((line = packet_read_line(process->out, NULL))) {
		const char *path;
		if (skip_prefix(line, "pathname=", &path))
			string_list_insert(available_paths, xstrdup(path));
		else
			; /* ignore unknown keys */
	}

	err = subprocess_read_status(process->out, &filter_status);
	if (err)
		goto done;

	err = strcmp(filter_status.buf, "success");

done:
	sigchain_pop(SIGPIPE);

	if (err)
		handle_filter_error(&filter_status, entry, 0);
	return !err;
}