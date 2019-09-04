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
struct write_each_note_data {struct non_note* next_non_note; int /*<<< orphan*/  root; } ;
struct non_note {struct non_note* next; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 
 int write_each_note_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_each_non_note_until(const char *note_path,
		struct write_each_note_data *d)
{
	struct non_note *n = d->next_non_note;
	int cmp = 0, ret;
	while (n && (!note_path || (cmp = strcmp(n->path, note_path)) <= 0)) {
		if (note_path && cmp == 0)
			; /* do nothing, prefer note to non-note */
		else {
			ret = write_each_note_helper(d->root, n->path, n->mode,
						     &n->oid);
			if (ret)
				return ret;
		}
		n = n->next;
	}
	d->next_non_note = n;
	return 0;
}