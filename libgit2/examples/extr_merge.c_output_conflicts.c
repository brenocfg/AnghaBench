#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index_conflict_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_index_conflict_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_conflict_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_index_conflict_next (TYPE_1__ const**,TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void output_conflicts(git_index *index)
{
	git_index_conflict_iterator *conflicts;
	const git_index_entry *ancestor;
	const git_index_entry *our;
	const git_index_entry *their;
	int err = 0;

	check_lg2(git_index_conflict_iterator_new(&conflicts, index), "failed to create conflict iterator", NULL);

	while ((err = git_index_conflict_next(&ancestor, &our, &their, conflicts)) == 0) {
		fprintf(stderr, "conflict: a:%s o:%s t:%s\n",
		        ancestor ? ancestor->path : "NULL",
		        our->path ? our->path : "NULL",
		        their->path ? their->path : "NULL");
	}

	if (err != GIT_ITEROVER) {
		fprintf(stderr, "error iterating conflicts\n");
	}

	git_index_conflict_iterator_free(conflicts);
}