#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  oid_hex ;
struct TYPE_4__ {char* name; char* email; } ;
typedef  TYPE_1__ git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  check_error (int,char*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_commit_author (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_parent (int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void commit_parsing(git_repository *repo)
{
	const git_signature *author, *cmtter;
	git_commit *commit, *parent;
	git_oid oid;
	char oid_hex[GIT_OID_HEXSZ+1];
	const char *message;
	unsigned int parents, p;
	int error;
	time_t time;

	printf("\n*Commit Parsing*\n");

	git_oid_fromstr(&oid, "8496071c1b46c854b31185ea97743be6a8774479");

	error = git_commit_lookup(&commit, repo, &oid);
	check_error(error, "looking up commit");

	/**
	 * Each of the properties of the commit object are accessible via methods,
	 * including commonly needed variations, such as `git_commit_time` which
	 * returns the author time and `git_commit_message` which gives you the
	 * commit message (as a NUL-terminated string).
	 */
	message  = git_commit_message(commit);
	author   = git_commit_author(commit);
	cmtter   = git_commit_committer(commit);
	time    = git_commit_time(commit);

	/**
	 * The author and committer methods return [git_signature] structures,
	 * which give you name, email and `when`, which is a `git_time` structure,
	 * giving you a timestamp and timezone offset.
	 */
	printf("Author: %s (%s)\nCommitter: %s (%s)\nDate: %s\nMessage: %s\n",
		author->name, author->email,
		cmtter->name, cmtter->email,
		ctime(&time), message);

	/**
	 * Commits can have zero or more parents. The first (root) commit will
	 * have no parents, most commits will have one (i.e. the commit it was
	 * based on) and merge commits will have two or more.  Commits can
	 * technically have any number, though it's rare to have more than two.
	 */
	parents  = git_commit_parentcount(commit);
	for (p = 0;p < parents;p++) {
		memset(oid_hex, 0, sizeof(oid_hex));

		git_commit_parent(&parent, commit, p);
		git_oid_fmt(oid_hex, git_commit_id(parent));
		printf("Parent: %s\n", oid_hex);
		git_commit_free(parent);
	}

	git_commit_free(commit);
}