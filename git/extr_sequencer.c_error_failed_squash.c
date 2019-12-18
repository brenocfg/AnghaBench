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
struct repository {int dummy; } ;
struct replay_opts {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ copy_file (char*,char*,int) ; 
 int error (int /*<<< orphan*/ ,char*,char*) ; 
 int error_with_patch (struct repository*,struct commit*,char const*,int,struct replay_opts*,int,int /*<<< orphan*/ ) ; 
 char* git_path_merge_msg (struct repository*) ; 
 char* rebase_path_message () ; 
 char* rebase_path_squash_msg () ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int error_failed_squash(struct repository *r,
			       struct commit *commit,
			       struct replay_opts *opts,
			       int subject_len,
			       const char *subject)
{
	if (copy_file(rebase_path_message(), rebase_path_squash_msg(), 0666))
		return error(_("could not copy '%s' to '%s'"),
			rebase_path_squash_msg(), rebase_path_message());
	unlink(git_path_merge_msg(r));
	if (copy_file(git_path_merge_msg(r), rebase_path_message(), 0666))
		return error(_("could not copy '%s' to '%s'"),
			     rebase_path_message(),
			     git_path_merge_msg(r));
	return error_with_patch(r, commit, subject, subject_len, opts, 1, 0);
}