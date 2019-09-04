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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object_t ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  check_error (int,char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 char* git_object_type2string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tag_free (int /*<<< orphan*/ *) ; 
 int git_tag_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* git_tag_message (int /*<<< orphan*/ *) ; 
 char* git_tag_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_target_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void tag_parsing(git_repository *repo)
{
	git_commit *commit;
	git_object_t type;
	git_tag *tag;
	git_oid oid;
	const char *name, *message;
	int error;

	printf("\n*Tag Parsing*\n");

	/**
	 * We create an oid for the tag object if we know the SHA and look it up
	 * the same way that we would a commit (or any other object).
	 */
	git_oid_fromstr(&oid, "b25fa35b38051e4ae45d4222e795f9df2e43f1d1");

	error = git_tag_lookup(&tag, repo, &oid);
	check_error(error, "looking up tag");

	/**
	 * Now that we have the tag object, we can extract the information it
	 * generally contains: the target (usually a commit object), the type of
	 * the target object (usually 'commit'), the name ('v1.0'), the tagger (a
	 * git_signature - name, email, timestamp), and the tag message.
	 */
	git_tag_target((git_object **)&commit, tag);
	name = git_tag_name(tag);		/* "test" */
	type = git_tag_target_type(tag);	/* GIT_OBJECT_COMMIT (object_t enum) */
	message = git_tag_message(tag);		/* "tag message\n" */
	printf("Tag Name: %s\nTag Type: %s\nTag Message: %s\n",
		name, git_object_type2string(type), message);

	/**
	 * Free both the commit and tag after usage.
	 */
	git_commit_free(commit);
	git_tag_free(tag);
}