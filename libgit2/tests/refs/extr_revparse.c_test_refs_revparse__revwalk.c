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
 int /*<<< orphan*/  assert_invalid_single_spec (char*) ; 
 int /*<<< orphan*/  test_object (char*,char*) ; 

void test_refs_revparse__revwalk(void)
{
	test_object("master^{/not found in any commit}", NULL);
	test_object("master^{/merge}", NULL);
	assert_invalid_single_spec("master^{/((}");

	test_object("master^{/anoth}", "5b5b025afb0b4c913b4c338a42934a3863bf3644");
	test_object("master^{/Merge}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
	test_object("br2^{/Merge}", "a4a7dce85cf63874e984719f4fdd239f5145052f");
	test_object("master^{/fo.rth}", "9fd738e8f7967c078dceed8190330fc8648ee56a");
}