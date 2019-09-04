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
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_peel_generic (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 

__attribute__((used)) static void assert_peel(
	const char *ref_name,
	git_object_t requested_type,
	const char* expected_sha,
	git_object_t expected_type)
{
	assert_peel_generic(g_repo, ref_name, requested_type,
			    expected_sha, expected_type);
}