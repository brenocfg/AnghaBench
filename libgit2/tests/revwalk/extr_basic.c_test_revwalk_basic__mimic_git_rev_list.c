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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_SORT_TIME ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_push_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 

void test_revwalk_basic__mimic_git_rev_list(void)
{
   git_oid oid;

   revwalk_basic_setup_walk(NULL);
   git_revwalk_sorting(_walk, GIT_SORT_TIME);

   cl_git_pass(git_revwalk_push_ref(_walk, "refs/heads/br2"));
   cl_git_pass(git_revwalk_push_ref(_walk, "refs/heads/master"));
   cl_git_pass(git_oid_fromstr(&oid, "e90810b8df3e80c413d903f631643c716887138d"));
   cl_git_pass(git_revwalk_push(_walk, &oid));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "e90810b8df3e80c413d903f631643c716887138d"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "6dcf9bf7541ee10456529833502442f385010c3d"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "a4a7dce85cf63874e984719f4fdd239f5145052f"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "be3563ae3f795b2b4353bcce3a527ad0a4f7f644"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "c47800c7266a2be04c571c04d5a6614691ea99bd"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "9fd738e8f7967c078dceed8190330fc8648ee56a"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "4a202b346bb0fb0db7eff3cffeb3c70babbd2045"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "5b5b025afb0b4c913b4c338a42934a3863bf3644"));

   cl_git_pass(git_revwalk_next(&oid, _walk));
   cl_assert(!git_oid_streq(&oid, "8496071c1b46c854b31185ea97743be6a8774479"));

   cl_git_fail_with(git_revwalk_next(&oid, _walk), GIT_ITEROVER);
}