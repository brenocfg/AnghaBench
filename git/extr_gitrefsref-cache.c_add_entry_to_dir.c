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
struct ref_entry {int /*<<< orphan*/  name; } ;
struct ref_dir {int nr; int sorted; struct ref_entry** entries; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct ref_entry**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void add_entry_to_dir(struct ref_dir *dir, struct ref_entry *entry)
{
	ALLOC_GROW(dir->entries, dir->nr + 1, dir->alloc);
	dir->entries[dir->nr++] = entry;
	/* optimize for the case that entries are added in order */
	if (dir->nr == 1 ||
	    (dir->nr == dir->sorted + 1 &&
	     strcmp(dir->entries[dir->nr - 2]->name,
		    dir->entries[dir->nr - 1]->name) < 0))
		dir->sorted = dir->nr;
}