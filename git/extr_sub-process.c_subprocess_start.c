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
typedef  int (* subprocess_start_fn ) (struct subprocess_entry*) ;
struct child_process {int use_shell; int in; int out; int clean_on_exit; char* trace2_child_class; int /*<<< orphan*/  clean_on_exit_handler; int /*<<< orphan*/  args; } ;
struct subprocess_entry {char const* cmd; int /*<<< orphan*/  ent; struct child_process process; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  child_process_init (struct child_process*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int start_command (struct child_process*) ; 
 int /*<<< orphan*/  strhash (char const*) ; 
 int /*<<< orphan*/  subprocess_exit_handler ; 
 int /*<<< orphan*/  subprocess_stop (struct hashmap*,struct subprocess_entry*) ; 

int subprocess_start(struct hashmap *hashmap, struct subprocess_entry *entry, const char *cmd,
	subprocess_start_fn startfn)
{
	int err;
	struct child_process *process;

	entry->cmd = cmd;
	process = &entry->process;

	child_process_init(process);
	argv_array_push(&process->args, cmd);
	process->use_shell = 1;
	process->in = -1;
	process->out = -1;
	process->clean_on_exit = 1;
	process->clean_on_exit_handler = subprocess_exit_handler;
	process->trace2_child_class = "subprocess";

	err = start_command(process);
	if (err) {
		error("cannot fork to run subprocess '%s'", cmd);
		return err;
	}

	hashmap_entry_init(&entry->ent, strhash(cmd));

	err = startfn(entry);
	if (err) {
		error("initialization for subprocess '%s' failed", cmd);
		subprocess_stop(hashmap, entry);
		return err;
	}

	hashmap_add(hashmap, &entry->ent);
	return 0;
}