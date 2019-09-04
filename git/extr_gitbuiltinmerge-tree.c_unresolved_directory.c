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
struct tree_desc {int dummy; } ;
struct traverse_info {int dummy; } ;
struct name_entry {int /*<<< orphan*/  oid; scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (scalar_t__) ; 
 void* fill_tree_descriptor (struct tree_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  merge_trees (struct tree_desc*,char*) ; 
 char* traverse_path (struct traverse_info const*,struct name_entry*) ; 

__attribute__((used)) static void unresolved_directory(const struct traverse_info *info,
				 struct name_entry n[3])
{
	char *newbase;
	struct name_entry *p;
	struct tree_desc t[3];
	void *buf0, *buf1, *buf2;

	for (p = n; p < n + 3; p++) {
		if (p->mode && S_ISDIR(p->mode))
			break;
	}
	if (n + 3 <= p)
		return; /* there is no tree here */

	newbase = traverse_path(info, p);

#define ENTRY_OID(e) (((e)->mode && S_ISDIR((e)->mode)) ? &(e)->oid : NULL)
	buf0 = fill_tree_descriptor(t + 0, ENTRY_OID(n + 0));
	buf1 = fill_tree_descriptor(t + 1, ENTRY_OID(n + 1));
	buf2 = fill_tree_descriptor(t + 2, ENTRY_OID(n + 2));
#undef ENTRY_OID

	merge_trees(t, newbase);

	free(buf0);
	free(buf1);
	free(buf2);
	free(newbase);
}