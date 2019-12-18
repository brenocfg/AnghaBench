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
struct diff_queue_struct {int /*<<< orphan*/  nr; } ;
struct diff_options {int /*<<< orphan*/  diff_path_counter; int /*<<< orphan*/  repo; } ;
struct diff_filespec {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  RUN_USING_SHELL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_external_diff_name (int /*<<< orphan*/ ,struct argv_array*,char const*,struct diff_filespec*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  diff_free_filespec_data (struct diff_filespec*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  remove_tempfile () ; 
 scalar_t__ run_command_v_opt_cd_env (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_external_diff(const char *pgm,
			      const char *name,
			      const char *other,
			      struct diff_filespec *one,
			      struct diff_filespec *two,
			      const char *xfrm_msg,
			      struct diff_options *o)
{
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct argv_array env = ARGV_ARRAY_INIT;
	struct diff_queue_struct *q = &diff_queued_diff;

	argv_array_push(&argv, pgm);
	argv_array_push(&argv, name);

	if (one && two) {
		add_external_diff_name(o->repo, &argv, name, one);
		if (!other)
			add_external_diff_name(o->repo, &argv, name, two);
		else {
			add_external_diff_name(o->repo, &argv, other, two);
			argv_array_push(&argv, other);
			argv_array_push(&argv, xfrm_msg);
		}
	}

	argv_array_pushf(&env, "GIT_DIFF_PATH_COUNTER=%d", ++o->diff_path_counter);
	argv_array_pushf(&env, "GIT_DIFF_PATH_TOTAL=%d", q->nr);

	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
	if (run_command_v_opt_cd_env(argv.argv, RUN_USING_SHELL, NULL, env.argv))
		die(_("external diff died, stopping at %s"), name);

	remove_tempfile();
	argv_array_clear(&argv);
	argv_array_clear(&env);
}