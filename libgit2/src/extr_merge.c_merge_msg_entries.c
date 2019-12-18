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
struct merge_msg_entry {int dummy; } ;
typedef  int /*<<< orphan*/  git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  git_vector_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,struct merge_msg_entry*) ; 

__attribute__((used)) static int merge_msg_entries(
	git_vector *v,
	const struct merge_msg_entry *entries,
	size_t len,
	int (*match)(const struct merge_msg_entry *entry, git_vector *entries))
{
	size_t i;
	int matches, total = 0;

	git_vector_clear(v);

	for (i = 0; i < len; i++) {
		if ((matches = match(&entries[i], v)) < 0)
			return matches;
		else if (!matches)
			continue;

		git_vector_insert(v, (struct merge_msg_entry *)&entries[i]);
		total++;
	}

	return total;
}