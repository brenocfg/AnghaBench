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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ERROR ; 
 int commit_count ; 
 int get_commit_index (int /*<<< orphan*/ *) ; 
 scalar_t__ git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  result_bytes ; 

__attribute__((used)) static int test_walk_only(git_revwalk *walk,
		const int possible_results[][commit_count], int results_count)
{
	git_oid oid;
	int i;
	int result_array[commit_count];

	for (i = 0; i < commit_count; ++i)
		result_array[i] = -1;

	i = 0;
	while (git_revwalk_next(&oid, walk) == 0) {
		result_array[i++] = get_commit_index(&oid);
		/*{
			char str[GIT_OID_HEXSZ+1];
			git_oid_fmt(str, &oid);
			str[GIT_OID_HEXSZ] = 0;
			printf("  %d) %s\n", i, str);
		}*/
	}

	for (i = 0; i < results_count; ++i)
		if (memcmp(possible_results[i],
				result_array, result_bytes) == 0)
			return 0;

	return GIT_ERROR;
}