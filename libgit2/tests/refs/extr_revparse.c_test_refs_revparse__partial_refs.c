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

void test_refs_revparse__partial_refs(void)
{
	test_object("point_to_blob", "1385f264afb75a56a5bec74243be9b367ba4ca08");
	test_object("packed-test", "4a202b346bb0fb0db7eff3cffeb3c70babbd2045");
	test_object("br2", "a4a7dce85cf63874e984719f4fdd239f5145052f");
}