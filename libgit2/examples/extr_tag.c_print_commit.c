#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* opts; } ;
typedef  TYPE_2__ tag_state ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_5__ {scalar_t__ num_lines; } ;

/* Variables and functions */
 char* git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_list_lines (char const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_commit(git_commit *commit, const char *name,
		const tag_state *state)
{
	printf("%-16s", name);

	if (state->opts->num_lines) {
		const char *msg = git_commit_message(commit);
		print_list_lines(msg, state);
	} else {
		printf("\n");
	}
}