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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  packall () ; 

void test_refs_pack__symbolic(void)
{
	/* create a packfile from loose refs skipping symbolic refs */
	int i;
	git_oid head;
	git_reference *ref;
	char name[128];

	cl_git_pass(git_reference_name_to_id(&head, g_repo, "HEAD"));

	/* make a bunch of references */

	for (i = 0; i < 100; ++i) {
		p_snprintf(name, sizeof(name), "refs/heads/symbolic-%03d", i);
		cl_git_pass(git_reference_symbolic_create(
			&ref, g_repo, name, "refs/heads/master", 0, NULL));
		git_reference_free(ref);

		p_snprintf(name, sizeof(name), "refs/heads/direct-%03d", i);
		cl_git_pass(git_reference_create(&ref, g_repo, name, &head, 0, NULL));
		git_reference_free(ref);
	}

	packall();
}