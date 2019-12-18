#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  real_name; } ;
typedef  TYPE_1__ git_mailmap_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_mailmap_entry_lookup (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mailmap ; 

void test_mailmap_basic__lookup(void)
{
	const git_mailmap_entry *entry = git_mailmap_entry_lookup(
		mailmap, "Typoed the name once", "foo@baz.com");
	cl_assert(entry);
	cl_assert_equal_s(entry->real_name, "Foo bar");
}