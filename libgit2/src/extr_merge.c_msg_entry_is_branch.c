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
struct merge_msg_entry {scalar_t__ written; TYPE_1__* merge_head; } ;
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_2__ {int /*<<< orphan*/ * ref_name; int /*<<< orphan*/ * remote_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ git__strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msg_entry_is_branch(
	const struct merge_msg_entry *entry,
	git_vector *entries)
{
	GIT_UNUSED(entries);

	return (entry->written == 0 &&
		entry->merge_head->remote_url == NULL &&
		entry->merge_head->ref_name != NULL &&
		git__strncmp(GIT_REFS_HEADS_DIR, entry->merge_head->ref_name, strlen(GIT_REFS_HEADS_DIR)) == 0);
}