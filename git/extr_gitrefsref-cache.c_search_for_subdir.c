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
struct ref_entry {int dummy; } ;
struct ref_dir {struct ref_entry** entries; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry_to_dir (struct ref_dir*,struct ref_entry*) ; 
 struct ref_entry* create_dir_entry (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 struct ref_dir* get_ref_dir (struct ref_entry*) ; 
 int search_ref_dir (struct ref_dir*,char const*,size_t) ; 

__attribute__((used)) static struct ref_dir *search_for_subdir(struct ref_dir *dir,
					 const char *subdirname, size_t len,
					 int mkdir)
{
	int entry_index = search_ref_dir(dir, subdirname, len);
	struct ref_entry *entry;
	if (entry_index == -1) {
		if (!mkdir)
			return NULL;
		/*
		 * Since dir is complete, the absence of a subdir
		 * means that the subdir really doesn't exist;
		 * therefore, create an empty record for it but mark
		 * the record complete.
		 */
		entry = create_dir_entry(dir->cache, subdirname, len, 0);
		add_entry_to_dir(dir, entry);
	} else {
		entry = dir->entries[entry_index];
	}
	return get_ref_dir(entry);
}