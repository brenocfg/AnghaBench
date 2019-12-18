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
struct replay_opts {int dummy; } ;
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  delete_reflog (char*) ; 
 int error_errno (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_dir () ; 
 scalar_t__ mkdir_in_gitdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_interactive () ; 
 int write_basic_state (struct replay_opts*,char const*,struct commit*,char const*) ; 

__attribute__((used)) static int init_basic_state(struct replay_opts *opts, const char *head_name,
			    struct commit *onto, const char *orig_head)
{
	FILE *interactive;

	if (!is_directory(merge_dir()) && mkdir_in_gitdir(merge_dir()))
		return error_errno(_("could not create temporary %s"), merge_dir());

	delete_reflog("REBASE_HEAD");

	interactive = fopen(path_interactive(), "w");
	if (!interactive)
		return error_errno(_("could not mark as interactive"));
	fclose(interactive);

	return write_basic_state(opts, head_name, onto, orig_head);
}