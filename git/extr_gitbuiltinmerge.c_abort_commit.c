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
struct commit_list {int dummy; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_merge_state (struct commit_list*) ; 

__attribute__((used)) static void abort_commit(struct commit_list *remoteheads, const char *err_msg)
{
	if (err_msg)
		error("%s", err_msg);
	fprintf(stderr,
		_("Not committing merge; use 'git commit' to complete the merge.\n"));
	write_merge_state(remoteheads);
	exit(1);
}