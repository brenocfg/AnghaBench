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
 int /*<<< orphan*/  test_read_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  two ; 
 int /*<<< orphan*/  zero ; 

void test_odb_loose__read_header(void)
{
	test_read_header(&commit);
	test_read_header(&tree);
	test_read_header(&tag);
	test_read_header(&zero);
	test_read_header(&one);
	test_read_header(&two);
	test_read_header(&some);
}