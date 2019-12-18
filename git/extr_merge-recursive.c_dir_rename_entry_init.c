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
struct dir_rename_entry {char* dir; int /*<<< orphan*/  possible_new_dirs; int /*<<< orphan*/  new_dir; scalar_t__ non_unique_new_dir; int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strhash (char*) ; 
 int /*<<< orphan*/  string_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dir_rename_entry_init(struct dir_rename_entry *entry,
				  char *directory)
{
	hashmap_entry_init(&entry->ent, strhash(directory));
	entry->dir = directory;
	entry->non_unique_new_dir = 0;
	strbuf_init(&entry->new_dir, 0);
	string_list_init(&entry->possible_new_dirs, 0);
}