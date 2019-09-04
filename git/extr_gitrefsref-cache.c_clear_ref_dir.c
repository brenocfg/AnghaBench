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
struct ref_dir {int nr; int sorted; int alloc; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ref_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_ref_dir(struct ref_dir *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++)
		free_ref_entry(dir->entries[i]);
	FREE_AND_NULL(dir->entries);
	dir->sorted = dir->nr = dir->alloc = 0;
}