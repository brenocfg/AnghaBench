#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_10__ {TYPE_2__* head_to_index; } ;
typedef  TYPE_3__ git_status_entry ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_11__ {int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ git_rebase_operation ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_annotated_commit ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_9__ {TYPE_1__ new_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EUNMERGED ; 
 int GIT_REBASE_OPERATION_PICK ; 
 int /*<<< orphan*/  cl_assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_file (char const*,int,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_rebase_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_next (TYPE_4__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* git_status_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int strlen (char const*) ; 

void test_rebase_merge__next_with_conflicts(void)
{
	git_rebase *rebase;
	git_reference *branch_ref, *upstream_ref;
	git_annotated_commit *branch_head, *upstream_head;
	git_rebase_operation *rebase_operation;
	git_status_list *status_list;
	const git_status_entry *status_entry;
	git_oid pick_id, commit_id;

	const char *expected_merge =
"ASPARAGUS SOUP.\n"
"\n"
"<<<<<<< master\n"
"TAKE FOUR LARGE BUNCHES of asparagus, scrape it nicely, cut off one inch\n"
"OF THE TOPS, and lay them in water, chop the stalks and put them on the\n"
"FIRE WITH A PIECE OF BACON, a large onion cut up, and pepper and salt;\n"
"ADD TWO QUARTS OF WATER, boil them till the stalks are quite soft, then\n"
"PULP THEM THROUGH A SIEVE, and strain the water to it, which must be put\n"
"=======\n"
"Take four large bunches of asparagus, scrape it nicely, CUT OFF ONE INCH\n"
"of the tops, and lay them in water, chop the stalks and PUT THEM ON THE\n"
"fire with a piece of bacon, a large onion cut up, and pepper and salt;\n"
"add two quarts of water, boil them till the stalks are quite soft, then\n"
"pulp them through a sieve, and strain the water to it, which must be put\n"
">>>>>>> Conflicting modification 1 to asparagus\n"
"back in the pot; put into it a chicken cut up, with the tops of\n"
"asparagus which had been laid by, boil it until these last articles are\n"
"sufficiently done, thicken with flour, butter and milk, and serve it up.\n";

	cl_git_pass(git_reference_lookup(&branch_ref, repo, "refs/heads/asparagus"));
	cl_git_pass(git_reference_lookup(&upstream_ref, repo, "refs/heads/master"));

	cl_git_pass(git_annotated_commit_from_ref(&branch_head, repo, branch_ref));
	cl_git_pass(git_annotated_commit_from_ref(&upstream_head, repo, upstream_ref));

	cl_git_pass(git_rebase_init(&rebase, repo, branch_head, upstream_head, NULL, NULL));

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));

	git_oid_fromstr(&pick_id, "33f915f9e4dbd9f4b24430e48731a59b45b15500");

	cl_assert_equal_i(GIT_REBASE_OPERATION_PICK, rebase_operation->type);
	cl_assert_equal_oid(&pick_id, &rebase_operation->id);
	cl_assert_equal_file("33f915f9e4dbd9f4b24430e48731a59b45b15500\n", 41, "rebase/.git/rebase-merge/current");
	cl_assert_equal_file("1\n", 2, "rebase/.git/rebase-merge/msgnum");

	cl_git_pass(git_status_list_new(&status_list, repo, NULL));
	cl_assert_equal_i(1, git_status_list_entrycount(status_list));
	cl_assert(status_entry = git_status_byindex(status_list, 0));

	cl_assert_equal_s("asparagus.txt", status_entry->head_to_index->new_file.path);

	cl_assert_equal_file(expected_merge, strlen(expected_merge), "rebase/asparagus.txt");

	cl_git_fail_with(GIT_EUNMERGED, git_rebase_commit(&commit_id, rebase, NULL, signature, NULL, NULL));

	git_status_list_free(status_list);
	git_annotated_commit_free(branch_head);
	git_annotated_commit_free(upstream_head);
	git_reference_free(branch_ref);
	git_reference_free(upstream_ref);
	git_rebase_free(rebase);
}