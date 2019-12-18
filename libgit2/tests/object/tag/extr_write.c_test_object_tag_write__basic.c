#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tag ;
struct TYPE_7__ {int time; int offset; } ;
struct TYPE_8__ {TYPE_1__ when; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_signature_new (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_message (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_tag_tagger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_target_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tagged_commit ; 
 int /*<<< orphan*/  tagger_email ; 
 int /*<<< orphan*/  tagger_message ; 
 int /*<<< orphan*/  tagger_name ; 

void test_object_tag_write__basic(void)
{
	/* write a tag to the repository and read it again */
	git_tag *tag;
	git_oid target_id, tag_id;
	git_signature *tagger;
	const git_signature *tagger1;
	git_reference *ref_tag;
	git_object *target;

	git_oid_fromstr(&target_id, tagged_commit);
	cl_git_pass(git_object_lookup(&target, g_repo, &target_id, GIT_OBJECT_COMMIT));

	/* create signature */
	cl_git_pass(git_signature_new(&tagger, tagger_name, tagger_email, 123456789, 60));

	cl_git_pass(
		git_tag_create(&tag_id, g_repo,
		  "the-tag", target, tagger, tagger_message, 0)
	);

	git_object_free(target);
	git_signature_free(tagger);

	cl_git_pass(git_tag_lookup(&tag, g_repo, &tag_id));
	cl_assert(git_oid_cmp(git_tag_target_id(tag), &target_id) == 0);

	/* Check attributes were set correctly */
	tagger1 = git_tag_tagger(tag);
	cl_assert(tagger1 != NULL);
	cl_assert_equal_s(tagger1->name, tagger_name);
	cl_assert_equal_s(tagger1->email, tagger_email);
	cl_assert(tagger1->when.time == 123456789);
	cl_assert(tagger1->when.offset == 60);

	cl_assert_equal_s(git_tag_message(tag), tagger_message);

	cl_git_pass(git_reference_lookup(&ref_tag, g_repo, "refs/tags/the-tag"));
	cl_assert(git_oid_cmp(git_reference_target(ref_tag), &tag_id) == 0);
	cl_git_pass(git_reference_delete(ref_tag));
	git_reference_free(ref_tag);

	git_tag_free(tag);
}