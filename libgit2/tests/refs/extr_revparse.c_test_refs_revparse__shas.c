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

void test_refs_revparse__shas(void)
{
	test_object("c47800c7266a2be04c571c04d5a6614691ea99bd", "c47800c7266a2be04c571c04d5a6614691ea99bd");
	test_object("c47800c", "c47800c7266a2be04c571c04d5a6614691ea99bd");
}