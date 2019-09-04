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
typedef  int /*<<< orphan*/  git_mailmap_entry ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  mailmap_entry_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mailmap_entry_replace(void **old_raw, void *new_raw)
{
	mailmap_entry_free((git_mailmap_entry *)*old_raw);
	*old_raw = new_raw;
	return GIT_EEXISTS;
}