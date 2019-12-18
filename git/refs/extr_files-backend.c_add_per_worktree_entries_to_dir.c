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
struct ref_dir {int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  add_entry_to_dir (struct ref_dir*,struct ref_entry*) ; 
 struct ref_entry* create_dir_entry (int /*<<< orphan*/ ,char const*,int,int) ; 
 int search_ref_dir (struct ref_dir*,char const*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void add_per_worktree_entries_to_dir(struct ref_dir *dir, const char *dirname)
{
	const char *prefixes[] = { "refs/bisect/", "refs/worktree/", "refs/rewritten/" };
	int ip;

	if (strcmp(dirname, "refs/"))
		return;

	for (ip = 0; ip < ARRAY_SIZE(prefixes); ip++) {
		const char *prefix = prefixes[ip];
		int prefix_len = strlen(prefix);
		struct ref_entry *child_entry;
		int pos;

		pos = search_ref_dir(dir, prefix, prefix_len);
		if (pos >= 0)
			continue;
		child_entry = create_dir_entry(dir->cache, prefix, prefix_len, 1);
		add_entry_to_dir(dir, child_entry);
	}
}