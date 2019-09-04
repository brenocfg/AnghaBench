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
struct expectations {int /*<<< orphan*/  encounters; scalar_t__ branch_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fail (char*) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static void assert_branch_has_been_found(struct expectations *findings, const char* expected_branch_name)
{
	int pos = 0;

	for (pos = 0; findings[pos].branch_name; ++pos) {
		if (strcmp(expected_branch_name, findings[pos].branch_name) == 0) {
			cl_assert_equal_i(1, findings[pos].encounters);
			return;
		}
	}

	cl_fail("expected branch not found in list.");
}