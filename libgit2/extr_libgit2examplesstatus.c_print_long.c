#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_15__ {int status; TYPE_6__* index_to_workdir; TYPE_3__* head_to_index; } ;
typedef  TYPE_7__ git_status_entry ;
struct TYPE_13__ {char* path; } ;
struct TYPE_12__ {char* path; } ;
struct TYPE_14__ {TYPE_5__ old_file; TYPE_4__ new_file; } ;
struct TYPE_10__ {char* path; } ;
struct TYPE_9__ {char* path; } ;
struct TYPE_11__ {TYPE_2__ new_file; TYPE_1__ old_file; } ;

/* Variables and functions */
 int GIT_STATUS_CURRENT ; 
 int GIT_STATUS_IGNORED ; 
 int GIT_STATUS_INDEX_DELETED ; 
 int GIT_STATUS_INDEX_MODIFIED ; 
 int GIT_STATUS_INDEX_NEW ; 
 int GIT_STATUS_INDEX_RENAMED ; 
 int GIT_STATUS_INDEX_TYPECHANGE ; 
 int GIT_STATUS_WT_DELETED ; 
 int GIT_STATUS_WT_MODIFIED ; 
 int GIT_STATUS_WT_NEW ; 
 int GIT_STATUS_WT_RENAMED ; 
 int GIT_STATUS_WT_TYPECHANGE ; 
 TYPE_7__* git_status_byindex (int /*<<< orphan*/ *,size_t) ; 
 size_t git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void print_long(git_status_list *status)
{
	size_t i, maxi = git_status_list_entrycount(status);
	const git_status_entry *s;
	int header = 0, changes_in_index = 0;
	int changed_in_workdir = 0, rm_in_workdir = 0;
	const char *old_path, *new_path;

	/** Print index changes. */

	for (i = 0; i < maxi; ++i) {
		char *istatus = NULL;

		s = git_status_byindex(status, i);

		if (s->status == GIT_STATUS_CURRENT)
			continue;

		if (s->status & GIT_STATUS_WT_DELETED)
			rm_in_workdir = 1;

		if (s->status & GIT_STATUS_INDEX_NEW)
			istatus = "new file: ";
		if (s->status & GIT_STATUS_INDEX_MODIFIED)
			istatus = "modified: ";
		if (s->status & GIT_STATUS_INDEX_DELETED)
			istatus = "deleted:  ";
		if (s->status & GIT_STATUS_INDEX_RENAMED)
			istatus = "renamed:  ";
		if (s->status & GIT_STATUS_INDEX_TYPECHANGE)
			istatus = "typechange:";

		if (istatus == NULL)
			continue;

		if (!header) {
			printf("# Changes to be committed:\n");
			printf("#   (use \"git reset HEAD <file>...\" to unstage)\n");
			printf("#\n");
			header = 1;
		}

		old_path = s->head_to_index->old_file.path;
		new_path = s->head_to_index->new_file.path;

		if (old_path && new_path && strcmp(old_path, new_path))
			printf("#\t%s  %s -> %s\n", istatus, old_path, new_path);
		else
			printf("#\t%s  %s\n", istatus, old_path ? old_path : new_path);
	}

	if (header) {
		changes_in_index = 1;
		printf("#\n");
	}
	header = 0;

	/** Print workdir changes to tracked files. */

	for (i = 0; i < maxi; ++i) {
		char *wstatus = NULL;

		s = git_status_byindex(status, i);

		/**
		 * With `GIT_STATUS_OPT_INCLUDE_UNMODIFIED` (not used in this example)
		 * `index_to_workdir` may not be `NULL` even if there are
		 * no differences, in which case it will be a `GIT_DELTA_UNMODIFIED`.
		 */
		if (s->status == GIT_STATUS_CURRENT || s->index_to_workdir == NULL)
			continue;

		/** Print out the output since we know the file has some changes */
		if (s->status & GIT_STATUS_WT_MODIFIED)
			wstatus = "modified: ";
		if (s->status & GIT_STATUS_WT_DELETED)
			wstatus = "deleted:  ";
		if (s->status & GIT_STATUS_WT_RENAMED)
			wstatus = "renamed:  ";
		if (s->status & GIT_STATUS_WT_TYPECHANGE)
			wstatus = "typechange:";

		if (wstatus == NULL)
			continue;

		if (!header) {
			printf("# Changes not staged for commit:\n");
			printf("#   (use \"git add%s <file>...\" to update what will be committed)\n", rm_in_workdir ? "/rm" : "");
			printf("#   (use \"git checkout -- <file>...\" to discard changes in working directory)\n");
			printf("#\n");
			header = 1;
		}

		old_path = s->index_to_workdir->old_file.path;
		new_path = s->index_to_workdir->new_file.path;

		if (old_path && new_path && strcmp(old_path, new_path))
			printf("#\t%s  %s -> %s\n", wstatus, old_path, new_path);
		else
			printf("#\t%s  %s\n", wstatus, old_path ? old_path : new_path);
	}

	if (header) {
		changed_in_workdir = 1;
		printf("#\n");
	}

	/** Print untracked files. */

	header = 0;

	for (i = 0; i < maxi; ++i) {
		s = git_status_byindex(status, i);

		if (s->status == GIT_STATUS_WT_NEW) {

			if (!header) {
				printf("# Untracked files:\n");
				printf("#   (use \"git add <file>...\" to include in what will be committed)\n");
				printf("#\n");
				header = 1;
			}

			printf("#\t%s\n", s->index_to_workdir->old_file.path);
		}
	}

	header = 0;

	/** Print ignored files. */

	for (i = 0; i < maxi; ++i) {
		s = git_status_byindex(status, i);

		if (s->status == GIT_STATUS_IGNORED) {

			if (!header) {
				printf("# Ignored files:\n");
				printf("#   (use \"git add -f <file>...\" to include in what will be committed)\n");
				printf("#\n");
				header = 1;
			}

			printf("#\t%s\n", s->index_to_workdir->old_file.path);
		}
	}

	if (!changes_in_index && changed_in_workdir)
		printf("no changes added to commit (use \"git add\" and/or \"git commit -a\")\n");
}