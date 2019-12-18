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
struct pathspec {int dummy; } ;
struct line_log_data {int /*<<< orphan*/  path; struct line_log_data* next; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  PATHSPEC_PREFER_FULL ; 
 char** argv_array_detach (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 

__attribute__((used)) static void parse_pathspec_from_ranges(struct pathspec *pathspec,
				       struct line_log_data *range)
{
	struct line_log_data *r;
	struct argv_array array = ARGV_ARRAY_INIT;
	const char **paths;

	for (r = range; r; r = r->next)
		argv_array_push(&array, r->path);
	paths = argv_array_detach(&array);

	parse_pathspec(pathspec, 0, PATHSPEC_PREFER_FULL, "", paths);
	/* strings are now owned by pathspec */
	free(paths);
}