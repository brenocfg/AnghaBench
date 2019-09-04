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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int error_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_seq_dir () ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int create_seq_dir(void)
{
	if (file_exists(git_path_seq_dir())) {
		error(_("a cherry-pick or revert is already in progress"));
		advise(_("try \"git cherry-pick (--continue | --quit | --abort)\""));
		return -1;
	} else if (mkdir(git_path_seq_dir(), 0777) < 0)
		return error_errno(_("could not create sequencer directory '%s'"),
				   git_path_seq_dir());
	return 0;
}