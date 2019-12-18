#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t file_count; char** files; scalar_t__ error_unmatch; } ;
typedef  TYPE_1__ ls_options ;
struct TYPE_7__ {char const* path; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_INDEX_STAGE_NORMAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t git_index_entrycount (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* git_index_get_bypath (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int print_paths(ls_options *opts, git_index *index)
{
	size_t i;
	const git_index_entry *entry;

	/* if there are no files explicitly listed by the user print all entries in the index */
	if (opts->file_count == 0) {
		size_t entry_count = git_index_entrycount(index);

		for (i = 0; i < entry_count; i++) {
			entry = git_index_get_byindex(index, i);
			puts(entry->path);
		}
		return 0;
	}

	/* loop through the files found in the args and print them if they exist */
	for (i = 0; i < opts->file_count; ++i) {
		const char *path = opts->files[i];

		if ((entry = git_index_get_bypath(index, path, GIT_INDEX_STAGE_NORMAL)) != NULL) {
			puts(path);
		} else if (opts->error_unmatch) {
			fprintf(stderr, "error: pathspec '%s' did not match any file(s) known to git.\n", path);
			fprintf(stderr, "Did you forget to 'git add'?\n");
			return -1;
		}
	}

	return 0;
}