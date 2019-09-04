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
struct print_payload {int options; int /*<<< orphan*/ * repo; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/ * git_index_matched_path_cb ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int SKIP ; 
 int UPDATE ; 
 int VERBOSE ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_all (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct print_payload*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_update_all (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,struct print_payload*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_array (TYPE_1__*,int,char**) ; 
 int /*<<< orphan*/  parse_opts (int*,int*,int,char**) ; 
 int /*<<< orphan*/  print_matched_cb ; 

int lg2_add(git_repository *repo, int argc, char** argv)
{
	git_index_matched_path_cb matched_cb = NULL;
	git_index *index;
	git_strarray array = {0};
	int options = 0, count = 0;
	struct print_payload payload = {0};

	parse_opts(&options, &count, argc, argv);
	init_array(&array, argc-count, argv+count);

	check_lg2(git_repository_index(&index, repo), "Could not open repository index", NULL);

	/* Setup a callback if the requested options need it */
	if ((options & VERBOSE) || (options & SKIP)) {
		matched_cb = &print_matched_cb;
	}

	/* Perform the requested action with the index and files */
	payload.options = options;
	payload.repo = repo;

	if (options & UPDATE) {
		git_index_update_all(index, &array, matched_cb, &payload);
	} else {
		git_index_add_all(index, &array, 0, matched_cb, &payload);
	}

	/* Cleanup memory */
	git_index_write(index);
	git_index_free(index);

	return 0;
}