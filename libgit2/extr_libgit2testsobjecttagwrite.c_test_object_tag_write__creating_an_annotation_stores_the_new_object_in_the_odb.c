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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_annotation (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_tag_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_name (int /*<<< orphan*/ *) ; 

void test_object_tag_write__creating_an_annotation_stores_the_new_object_in_the_odb(void)
{
	git_oid tag_id;
	git_tag *tag;

	create_annotation(&tag_id, "new_tag");

	cl_git_pass(git_tag_lookup(&tag, g_repo, &tag_id));
	cl_assert_equal_s("new_tag", git_tag_name(tag));

	git_tag_free(tag);
}