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
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bare_resolved_with_blob_override ; 
 int /*<<< orphan*/  check_mailmap_resolve (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_config ; 
 TYPE_1__* g_mailmap ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_mailmap_from_repository (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_length (int /*<<< orphan*/ *) ; 

void test_mailmap_parsing__bare_blob_config(void)
{
	g_repo = cl_git_sandbox_init("mailmap/.gitted");
	cl_git_pass(git_repository_set_bare(g_repo));
	cl_check(git_repository_is_bare(g_repo));

	cl_git_pass(git_repository_config(&g_config, g_repo));

	cl_git_pass(git_config_set_string(
		g_config, "mailmap.blob", "HEAD:blob_override"));

	cl_git_pass(git_mailmap_from_repository(&g_mailmap, g_repo));

	/* Check that we only have the 2 entries */
	cl_assert_equal_sz(git_vector_length(&g_mailmap->entries), 2);

	/* Check that resolving the entries works */
	check_mailmap_resolve(
		g_mailmap, bare_resolved_with_blob_override,
		ARRAY_SIZE(bare_resolved_with_blob_override));
}