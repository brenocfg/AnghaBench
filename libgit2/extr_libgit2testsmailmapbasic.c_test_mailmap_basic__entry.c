#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  replace_email; int /*<<< orphan*/  replace_name; int /*<<< orphan*/  real_email; int /*<<< orphan*/  real_name; } ;
typedef  TYPE_1__ git_mailmap_entry ;
struct TYPE_10__ {int /*<<< orphan*/  replace_email; int /*<<< orphan*/  replace_name; int /*<<< orphan*/  real_email; int /*<<< orphan*/  real_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,int /*<<< orphan*/ ) ; 
 TYPE_5__* expected ; 
 TYPE_1__* git_mailmap_entry_lookup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_length (int /*<<< orphan*/ *) ; 
 TYPE_2__* mailmap ; 

void test_mailmap_basic__entry(void)
{
	size_t idx;
	const git_mailmap_entry *entry;

	/* Check that we have the expected # of entries */
	cl_assert_equal_sz(ARRAY_SIZE(expected), git_vector_length(&mailmap->entries));

	for (idx = 0; idx < ARRAY_SIZE(expected); ++idx) {
		/* Try to look up each entry and make sure they match */
		entry = git_mailmap_entry_lookup(
			mailmap, expected[idx].replace_name, expected[idx].replace_email);

		cl_assert(entry);
		cl_assert_equal_s(entry->real_name, expected[idx].real_name);
		cl_assert_equal_s(entry->real_email, expected[idx].real_email);
		cl_assert_equal_s(entry->replace_name, expected[idx].replace_name);
		cl_assert_equal_s(entry->replace_email, expected[idx].replace_email);
	}
}