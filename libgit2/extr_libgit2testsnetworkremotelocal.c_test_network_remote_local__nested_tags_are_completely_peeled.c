#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote_head ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_to_local_repository (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_ls (TYPE_1__ const***,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void test_network_remote_local__nested_tags_are_completely_peeled(void)
{
	const git_remote_head **refs;
	size_t refs_len, i;

	connect_to_local_repository(cl_fixture("testrepo.git"));

	cl_git_pass(git_remote_ls(&refs, &refs_len, remote));

	for (i = 0; i < refs_len; i++) {
		if (!strcmp(refs[i]->name, "refs/tags/test^{}"))
			cl_git_pass(git_oid_streq(&refs[i]->oid, "e90810b8df3e80c413d903f631643c716887138d"));
	}
}