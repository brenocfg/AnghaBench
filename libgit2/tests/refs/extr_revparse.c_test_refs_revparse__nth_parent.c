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

void test_refs_revparse__nth_parent(void)
{
	assert_invalid_single_spec("be3563a^-1");
	assert_invalid_single_spec("^");
	assert_invalid_single_spec("be3563a^{tree}^");
	assert_invalid_single_spec("point_to_blob^{blob}^");
	assert_invalid_single_spec("this doesn't make sense^1");

	test_object("be3563a^1", "9fd738e8f7967c078dceed8190330fc8648ee56a");
	test_object("be3563a^", "9fd738e8f7967c078dceed8190330fc8648ee56a");
	test_object("be3563a^2", "c47800c7266a2be04c571c04d5a6614691ea99bd");
	test_object("be3563a^1^1", "4a202b346bb0fb0db7eff3cffeb3c70babbd2045");
	test_object("be3563a^^", "4a202b346bb0fb0db7eff3cffeb3c70babbd2045");
	test_object("be3563a^2^1", "5b5b025afb0b4c913b4c338a42934a3863bf3644");
	test_object("be3563a^0", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
	test_object("be3563a^{commit}^", "9fd738e8f7967c078dceed8190330fc8648ee56a");

	test_object("be3563a^42", NULL);
}