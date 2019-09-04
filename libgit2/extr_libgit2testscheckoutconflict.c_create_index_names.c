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
struct checkout_name_entry {int /*<<< orphan*/ * theirs; int /*<<< orphan*/ * ours; int /*<<< orphan*/ * ancestor; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  git_index_name_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_index_names(struct checkout_name_entry *entries, size_t entries_len)
{
	size_t i;

	for (i = 0; i < entries_len; i++) {
		cl_git_pass(git_index_name_add(g_index,
			strlen(entries[i].ancestor) == 0 ? NULL : entries[i].ancestor,
			strlen(entries[i].ours) == 0 ? NULL : entries[i].ours,
			strlen(entries[i].theirs) == 0 ? NULL : entries[i].theirs));
	}
}