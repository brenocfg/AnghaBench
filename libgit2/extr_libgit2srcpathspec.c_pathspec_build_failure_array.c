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
struct TYPE_6__ {size_t length; } ;
typedef  TYPE_1__ git_vector ;
typedef  int /*<<< orphan*/  git_pool ;
typedef  int /*<<< orphan*/  git_pathspec_string_array_t ;
typedef  int /*<<< orphan*/  git_bitvec ;
struct TYPE_7__ {int /*<<< orphan*/  pattern; } ;
typedef  TYPE_2__ git_attr_fnmatch ;

/* Variables and functions */
 char** git_array_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ git_bitvec_get (int /*<<< orphan*/ *,size_t) ; 
 char* git_pool_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* git_vector_get (TYPE_1__*,size_t) ; 

__attribute__((used)) static int pathspec_build_failure_array(
	git_pathspec_string_array_t *failures,
	git_vector *patterns,
	git_bitvec *used,
	git_pool *pool)
{
	size_t pos;
	char **failed;
	const git_attr_fnmatch *pat;

	for (pos = 0; pos < patterns->length; ++pos) {
		if (git_bitvec_get(used, pos))
			continue;

		if ((failed = git_array_alloc(*failures)) == NULL)
			return -1;

		pat = git_vector_get(patterns, pos);

		if ((*failed = git_pool_strdup(pool, pat->pattern)) == NULL)
			return -1;
	}

	return 0;
}