#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * replace_name; int /*<<< orphan*/ * replace_email; } ;
typedef  TYPE_1__ git_mailmap_entry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int git__strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mailmap_entry_cmp(const void *a_raw, const void *b_raw)
{
	const git_mailmap_entry *a = (const git_mailmap_entry *)a_raw;
	const git_mailmap_entry *b = (const git_mailmap_entry *)b_raw;
	int cmp;

	assert(a && b && a->replace_email && b->replace_email);

	cmp = git__strcmp(a->replace_email, b->replace_email);
	if (cmp)
		return cmp;

	/* NULL replace_names are less than not-NULL ones */
	if (a->replace_name == NULL || b->replace_name == NULL)
		return (int)(a->replace_name != NULL) - (int)(b->replace_name != NULL);

	return git__strcmp(a->replace_name, b->replace_name);
}