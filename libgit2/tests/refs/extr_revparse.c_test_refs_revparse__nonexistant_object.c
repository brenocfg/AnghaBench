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
 int /*<<< orphan*/  test_object (char*,int /*<<< orphan*/ *) ; 

void test_refs_revparse__nonexistant_object(void)
{
	test_object("this-does-not-exist", NULL);
	test_object("this-does-not-exist^1", NULL);
	test_object("this-does-not-exist~2", NULL);
}