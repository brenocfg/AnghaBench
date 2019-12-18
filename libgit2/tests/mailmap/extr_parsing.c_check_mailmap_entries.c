#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  replace_email; int /*<<< orphan*/  replace_name; int /*<<< orphan*/  real_email; int /*<<< orphan*/  real_name; } ;
typedef  TYPE_1__ mailmap_entry ;
struct TYPE_10__ {int /*<<< orphan*/  replace_email; int /*<<< orphan*/  replace_name; int /*<<< orphan*/  real_email; int /*<<< orphan*/  real_name; } ;
typedef  TYPE_2__ git_mailmap_entry ;
struct TYPE_11__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ git_mailmap ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_2__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,int /*<<< orphan*/ ) ; 
 TYPE_2__* git_mailmap_entry_lookup (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_mailmap_entries(
	const git_mailmap *mailmap, const mailmap_entry *entries, size_t entries_size)
{
	const git_mailmap_entry *parsed;
	size_t idx;

	/* Check the correct # of entries were parsed */
	cl_assert_equal_sz(entries_size, git_vector_length(&mailmap->entries));

	/* Make sure looking up each entry succeeds */
	for (idx = 0; idx < entries_size; ++idx) {
		parsed = git_mailmap_entry_lookup(
			mailmap, entries[idx].replace_name, entries[idx].replace_email);

		cl_assert(parsed);
		cl_assert_equal_s(parsed->real_name, entries[idx].real_name);
		cl_assert_equal_s(parsed->real_email, entries[idx].real_email);
		cl_assert_equal_s(parsed->replace_name, entries[idx].replace_name);
		cl_assert_equal_s(parsed->replace_email, entries[idx].replace_email);
	}
}