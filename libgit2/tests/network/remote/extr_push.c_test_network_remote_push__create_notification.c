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
struct TYPE_9__ {char** member_0; int member_1; } ;
typedef  TYPE_2__ git_strarray ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_10__ {char* src_refname; char* dst_refname; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
typedef  TYPE_3__ git_push_update ;
struct TYPE_8__ {TYPE_3__* payload; int /*<<< orphan*/  push_negotiation; } ;
struct TYPE_11__ {TYPE_1__ callbacks; } ;
typedef  TYPE_4__ git_push_options ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 TYPE_4__ GIT_PUSH_OPTIONS_INIT ; 
 int /*<<< orphan*/  _dummy ; 
 int /*<<< orphan*/  _remote ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_dummy_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_push (int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  negotiation_cb ; 

void test_network_remote_push__create_notification(void)
{
	git_push_options opts = GIT_PUSH_OPTIONS_INIT;
	git_reference *ref;
	git_push_update expected;
	char *refspec = "refs/heads/empty-tree";
	const git_strarray refspecs = {
		&refspec,
		1,
	};

	create_dummy_commit(&ref, _dummy);

	expected.src_refname = "refs/heads/empty-tree";
	expected.dst_refname = "refs/heads/empty-tree";
	git_oid_cpy(&expected.dst, git_reference_target(ref));
	memset(&expected.src, 0, sizeof(git_oid));

	opts.callbacks.push_negotiation = negotiation_cb;
	opts.callbacks.payload = &expected;
	cl_git_pass(git_remote_push(_remote, &refspecs, &opts));

	git_reference_free(ref);
	cl_git_pass(git_reference_lookup(&ref, _repo, "refs/heads/empty-tree"));
	git_reference_free(ref);
}