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

/* Variables and functions */
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  test_object_and_ref_inrepo (char const*,char const*,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_object_and_ref(const char *spec, const char *expected_oid, const char *expected_refname)
{
	test_object_and_ref_inrepo(spec, expected_oid, expected_refname, g_repo, true);
}