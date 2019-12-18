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
struct strbuf {char* buf; } ;
struct path_entry {int /*<<< orphan*/  entry; } ;
struct hashmap {int dummy; } ;
struct child_process {int no_stdin; int no_stdout; int no_stderr; int git_cmd; int clean_on_exit; char const* dir; char const** env; int out; scalar_t__ use_shell; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct path_entry*,int /*<<< orphan*/ ,char*) ; 
 struct strbuf STRBUF_INIT ; 
 char* absolute_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char const*,char*,char const*,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  run_command (struct child_process*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_getline_nul (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strhash (char*) ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 

__attribute__((used)) static void changed_files(struct hashmap *result, const char *index_path,
			  const char *workdir)
{
	struct child_process update_index = CHILD_PROCESS_INIT;
	struct child_process diff_files = CHILD_PROCESS_INIT;
	struct strbuf index_env = STRBUF_INIT, buf = STRBUF_INIT;
	const char *git_dir = absolute_path(get_git_dir()), *env[] = {
		NULL, NULL
	};
	FILE *fp;

	strbuf_addf(&index_env, "GIT_INDEX_FILE=%s", index_path);
	env[0] = index_env.buf;

	argv_array_pushl(&update_index.args,
			 "--git-dir", git_dir, "--work-tree", workdir,
			 "update-index", "--really-refresh", "-q",
			 "--unmerged", NULL);
	update_index.no_stdin = 1;
	update_index.no_stdout = 1;
	update_index.no_stderr = 1;
	update_index.git_cmd = 1;
	update_index.use_shell = 0;
	update_index.clean_on_exit = 1;
	update_index.dir = workdir;
	update_index.env = env;
	/* Ignore any errors of update-index */
	run_command(&update_index);

	argv_array_pushl(&diff_files.args,
			 "--git-dir", git_dir, "--work-tree", workdir,
			 "diff-files", "--name-only", "-z", NULL);
	diff_files.no_stdin = 1;
	diff_files.git_cmd = 1;
	diff_files.use_shell = 0;
	diff_files.clean_on_exit = 1;
	diff_files.out = -1;
	diff_files.dir = workdir;
	diff_files.env = env;
	if (start_command(&diff_files))
		die("could not obtain raw diff");
	fp = xfdopen(diff_files.out, "r");
	while (!strbuf_getline_nul(&buf, fp)) {
		struct path_entry *entry;
		FLEX_ALLOC_STR(entry, path, buf.buf);
		hashmap_entry_init(&entry->entry, strhash(buf.buf));
		hashmap_add(result, &entry->entry);
	}
	fclose(fp);
	if (finish_command(&diff_files))
		die("diff-files did not exit properly");
	strbuf_release(&index_env);
	strbuf_release(&buf);
}