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
typedef  int git_time_t ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_7__ {char* pattern; int /*<<< orphan*/  describe_strategy; } ;
typedef  TYPE_1__ git_describe_options ;
struct TYPE_8__ {int always_use_long_format; } ;
typedef  TYPE_2__ git_describe_format_options ;

/* Variables and functions */
 TYPE_2__ GIT_DESCRIBE_FORMAT_OPTIONS_INIT ; 
 TYPE_1__ GIT_DESCRIBE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DESCRIBE_TAGS ; 
 int /*<<< orphan*/  assert_describe (char*,char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_and_tag (int*,char*,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_describe_t6120__pattern(void)
{
	git_describe_options opts = GIT_DESCRIBE_OPTIONS_INIT;
	git_describe_format_options fmt_opts = GIT_DESCRIBE_FORMAT_OPTIONS_INIT;
	git_oid tag_id;
	git_object *head;
	git_signature *tagger;
	git_time_t time;

	/* set-up matching pattern tests */
	cl_git_pass(git_revparse_single(&head, repo, "HEAD"));

	time = 1380553019;
	cl_git_pass(git_signature_new(&tagger, "tagger", "tagger@libgit2.org", time, 0));
	cl_git_pass(git_tag_create(&tag_id, repo, "test-annotated", head, tagger, "test-annotated", 0));
	git_signature_free(tagger);
	git_object_free(head);

	commit_and_tag(&time, "one more", "refs/tags/test1-lightweight");
	commit_and_tag(&time, "yet another", "refs/tags/test2-lightweight");
	commit_and_tag(&time, "even more", NULL);


	/* Exercize */
	opts.pattern = "test-*";
	assert_describe("test-annotated-*", "HEAD", repo, &opts, &fmt_opts);

	opts.describe_strategy = GIT_DESCRIBE_TAGS;
	opts.pattern = "test1-*";
	assert_describe("test1-lightweight-*", "HEAD", repo, &opts, &fmt_opts);

	opts.pattern = "test2-*";
	assert_describe("test2-lightweight-*", "HEAD", repo, &opts, &fmt_opts);

	fmt_opts.always_use_long_format = 1;
	assert_describe("test2-lightweight-*", "HEAD^", repo, &opts, &fmt_opts);
}