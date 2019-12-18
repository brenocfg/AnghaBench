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
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 scalar_t__ GIT_INDEX_ENTRY_STAGE (int /*<<< orphan*/  const*) ; 

int git_index_entry_is_conflict(const git_index_entry *entry)
{
	return (GIT_INDEX_ENTRY_STAGE(entry) > 0);
}