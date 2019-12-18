#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_3__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_ignores ;
typedef  int /*<<< orphan*/  git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 int git_attr_cache__get (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_attr_file__free (int /*<<< orphan*/ *) ; 
 int git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_ignore_file ; 

__attribute__((used)) static int push_ignore_file(
	git_ignores *ignores,
	git_vector *which_list,
	const char *base,
	const char *filename)
{
	int error = 0;
	git_attr_file *file = NULL;

	error = git_attr_cache__get(&file, ignores->repo, NULL, GIT_ATTR_FILE__FROM_FILE,
				    base, filename, parse_ignore_file, false);
	if (error < 0)
		return error;

	if (file != NULL) {
		if ((error = git_vector_insert(which_list, file)) < 0)
			git_attr_file__free(file);
	}

	return error;
}