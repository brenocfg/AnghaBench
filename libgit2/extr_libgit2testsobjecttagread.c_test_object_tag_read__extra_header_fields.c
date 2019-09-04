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
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  silly_tag ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_object_tag_read__extra_header_fields(void)
{
	git_tag *tag;
	git_odb *odb;
	git_oid id;

	cl_git_pass(git_repository_odb__weakptr(&odb, g_repo));

	cl_git_pass(git_odb_write(&id, odb, silly_tag, strlen(silly_tag), GIT_OBJECT_TAG));
	cl_git_pass(git_tag_lookup(&tag, g_repo, &id));

	cl_assert_equal_s("v1_0_1 release\n", git_tag_message(tag));

	git_tag_free(tag);
}