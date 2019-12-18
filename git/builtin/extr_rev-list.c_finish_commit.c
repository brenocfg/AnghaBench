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
struct commit {int /*<<< orphan*/ * parents; } ;
struct TYPE_2__ {int /*<<< orphan*/  parsed_objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_buffer (int /*<<< orphan*/ ,struct commit*) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_repository ; 

__attribute__((used)) static void finish_commit(struct commit *commit)
{
	if (commit->parents) {
		free_commit_list(commit->parents);
		commit->parents = NULL;
	}
	free_commit_buffer(the_repository->parsed_objects,
			   commit);
}