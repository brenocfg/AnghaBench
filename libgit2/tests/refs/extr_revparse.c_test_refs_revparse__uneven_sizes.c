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

void test_refs_revparse__uneven_sizes(void)
{
	test_object("a65fedf39aefe402d3bb6e24df4d4f5fe454775",
				"a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	test_object("a65fedf39aefe402d3bb6e24df4d4f5fe45477",
				"a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	test_object("a65fedf39aefe402d3bb6e24df4d4f5fe4547",
				"a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	test_object("a65fedf39aefe402d3bb6e24df4d",
				"a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
}