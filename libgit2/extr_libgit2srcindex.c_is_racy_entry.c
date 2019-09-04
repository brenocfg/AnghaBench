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
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int git_index_entry_newer_than_index (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_racy_entry(git_index *index, const git_index_entry *entry)
{
	/* Git special-cases submodules in the check */
	if (S_ISGITLINK(entry->mode))
		return false;

	return git_index_entry_newer_than_index(entry, index);
}