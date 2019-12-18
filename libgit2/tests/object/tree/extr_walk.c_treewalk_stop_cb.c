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
typedef  char git_tree_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int treewalk_stop_cb(
	const char *root, const git_tree_entry *entry, void *payload)
{
	int *count = payload;

	GIT_UNUSED(root);
	GIT_UNUSED(entry);

	(*count) += 1;

	return (*count == 2) ? -123 : 0;
}