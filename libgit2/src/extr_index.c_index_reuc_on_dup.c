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

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  index_entry_reuc_free (void*) ; 

__attribute__((used)) static int index_reuc_on_dup(void **old, void *new)
{
	index_entry_reuc_free(*old);
	*old = new;
	return GIT_EEXISTS;
}