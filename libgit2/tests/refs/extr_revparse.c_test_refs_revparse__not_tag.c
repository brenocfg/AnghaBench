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
 int /*<<< orphan*/  test_object (char*,char*) ; 

void test_refs_revparse__not_tag(void)
{
	test_object("point_to_blob^{}", "1385f264afb75a56a5bec74243be9b367ba4ca08");
	test_object("wrapped_tag^{}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("master^{}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("master^{tree}^{}", "944c0f6e4dfa41595e6eb3ceecdb14f50fe18162");
	test_object("e90810b^{}", "e90810b8df3e80c413d903f631643c716887138d");
	test_object("tags/e90810b^{}", "e90810b8df3e80c413d903f631643c716887138d");
	test_object("e908^{}", "e90810b8df3e80c413d903f631643c716887138d");
}