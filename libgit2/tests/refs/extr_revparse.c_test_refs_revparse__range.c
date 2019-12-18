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
 int GIT_REVPARSE_MERGE_BASE ; 
 int GIT_REVPARSE_RANGE ; 
 int /*<<< orphan*/  assert_invalid_single_spec (char*) ; 
 int /*<<< orphan*/  test_rangelike (char*,char*,char*,int) ; 

void test_refs_revparse__range(void)
{
	assert_invalid_single_spec("be3563a^1..be3563a");

	test_rangelike("be3563a^1..be3563a",
	               "9fd738e8f7967c078dceed8190330fc8648ee56a",
	               "be3563ae3f795b2b4353bcce3a527ad0a4f7f644",
	               GIT_REVPARSE_RANGE);

	test_rangelike("be3563a^1...be3563a",
	               "9fd738e8f7967c078dceed8190330fc8648ee56a",
	               "be3563ae3f795b2b4353bcce3a527ad0a4f7f644",
	               GIT_REVPARSE_RANGE | GIT_REVPARSE_MERGE_BASE);

	test_rangelike("be3563a^1.be3563a", NULL, NULL, 0);
}