#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int GIT_INDEX_ENTRY_STAGE (TYPE_1__ const*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_index_entry_cmp(const void *a, const void *b)
{
	int diff;
	const git_index_entry *entry_a = a;
	const git_index_entry *entry_b = b;

	diff = strcmp(entry_a->path, entry_b->path);

	if (diff == 0)
		diff = (GIT_INDEX_ENTRY_STAGE(entry_a) - GIT_INDEX_ENTRY_STAGE(entry_b));

	return diff;
}