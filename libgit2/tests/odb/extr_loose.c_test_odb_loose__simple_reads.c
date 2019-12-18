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
 int /*<<< orphan*/  commit ; 
 int /*<<< orphan*/  one ; 
 int /*<<< orphan*/  some ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  test_read_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  two ; 
 int /*<<< orphan*/  zero ; 

void test_odb_loose__simple_reads(void)
{
	test_read_object(&commit);
	test_read_object(&tree);
	test_read_object(&tag);
	test_read_object(&zero);
	test_read_object(&one);
	test_read_object(&two);
	test_read_object(&some);
}