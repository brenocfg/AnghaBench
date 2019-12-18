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
struct pathspec {int nr; TYPE_1__* items; } ;
struct path_pattern {int dummy; } ;
struct dir_struct {int dummy; } ;
struct TYPE_2__ {char* match; int /*<<< orphan*/  original; } ;

/* Variables and functions */
 int DT_UNKNOWN ; 
 int PATHSPEC_ALL_MAGIC ; 
 int PATHSPEC_FROMTOP ; 
 int PATHSPEC_KEEP_ORDER ; 
 int PATHSPEC_SYMLINK_LEADING_PATH ; 
 int /*<<< orphan*/  die_path_inside_submodule (int /*<<< orphan*/ *,struct pathspec*) ; 
 char* find_pathspecs_matching_against_index (struct pathspec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct path_pattern* last_matching_pattern (struct dir_struct*,int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  output_pattern (int /*<<< orphan*/ ,struct path_pattern*) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int,int,char const*,char const**) ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ show_non_matching ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static int check_ignore(struct dir_struct *dir,
			const char *prefix, int argc, const char **argv)
{
	const char *full_path;
	char *seen;
	int num_ignored = 0, i;
	struct path_pattern *pattern;
	struct pathspec pathspec;

	if (!argc) {
		if (!quiet)
			fprintf(stderr, "no pathspec given.\n");
		return 0;
	}

	/*
	 * check-ignore just needs paths. Magic beyond :/ is really
	 * irrelevant.
	 */
	parse_pathspec(&pathspec,
		       PATHSPEC_ALL_MAGIC & ~PATHSPEC_FROMTOP,
		       PATHSPEC_SYMLINK_LEADING_PATH |
		       PATHSPEC_KEEP_ORDER,
		       prefix, argv);

	die_path_inside_submodule(&the_index, &pathspec);

	/*
	 * look for pathspecs matching entries in the index, since these
	 * should not be ignored, in order to be consistent with
	 * 'git status', 'git add' etc.
	 */
	seen = find_pathspecs_matching_against_index(&pathspec, &the_index);
	for (i = 0; i < pathspec.nr; i++) {
		full_path = pathspec.items[i].match;
		pattern = NULL;
		if (!seen[i]) {
			int dtype = DT_UNKNOWN;
			pattern = last_matching_pattern(dir, &the_index,
							full_path, &dtype);
		}
		if (!quiet && (pattern || show_non_matching))
			output_pattern(pathspec.items[i].original, pattern);
		if (pattern)
			num_ignored++;
	}
	free(seen);

	return num_ignored;
}