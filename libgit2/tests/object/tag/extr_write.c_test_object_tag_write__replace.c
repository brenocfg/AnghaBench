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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tagged_commit ; 
 int /*<<< orphan*/  tagger_email ; 
 int /*<<< orphan*/  tagger_message ; 
 int /*<<< orphan*/  tagger_name ; 

void test_object_tag_write__replace(void)
{
	/* Replace an already existing tag */
	git_oid target_id, tag_id, old_tag_id;
	git_signature *tagger;
	git_reference *ref_tag;
	git_object *target;

	git_oid_fromstr(&target_id, tagged_commit);
	cl_git_pass(git_object_lookup(&target, g_repo, &target_id, GIT_OBJECT_COMMIT));

	cl_git_pass(git_reference_lookup(&ref_tag, g_repo, "refs/tags/e90810b"));
	git_oid_cpy(&old_tag_id, git_reference_target(ref_tag));
	git_reference_free(ref_tag);

	/* create signature */
	cl_git_pass(git_signature_new(&tagger, tagger_name, tagger_email, 123456789, 60));

	cl_git_pass(git_tag_create(
                              &tag_id, /* out id */
                              g_repo,
                              "e90810b",
                              target,
                              tagger,
                              tagger_message,
                              1));

	git_object_free(target);
	git_signature_free(tagger);

	cl_git_pass(git_reference_lookup(&ref_tag, g_repo, "refs/tags/e90810b"));
	cl_assert(git_oid_cmp(git_reference_target(ref_tag), &tag_id) == 0);
	cl_assert(git_oid_cmp(git_reference_target(ref_tag), &old_tag_id) != 0);

	git_reference_free(ref_tag);
}