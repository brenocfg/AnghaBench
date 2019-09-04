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
typedef  int /*<<< orphan*/  git_revparse_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  test_id_inrepo (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_id(
	const char *spec,
	const char *expected_left,
	const char *expected_right,
	git_revparse_mode_t expected_flags)
{
	test_id_inrepo(spec, expected_left, expected_right, expected_flags, g_repo);
}