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
struct tree_desc {int /*<<< orphan*/  entry; scalar_t__ size; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (unsigned short) ; 
 int get_tree_entry (struct repository*,struct object_id*,char const*,struct object_id*,unsigned short*) ; 
 int memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int strlen (char const*) ; 
 struct object_id* tree_entry_extract (struct tree_desc*,char const**,unsigned short*) ; 
 int tree_entry_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_tree_entry (struct tree_desc*) ; 

__attribute__((used)) static int find_tree_entry(struct repository *r, struct tree_desc *t,
			   const char *name, struct object_id *result,
			   unsigned short *mode)
{
	int namelen = strlen(name);
	while (t->size) {
		const char *entry;
		struct object_id oid;
		int entrylen, cmp;

		oidcpy(&oid, tree_entry_extract(t, &entry, mode));
		entrylen = tree_entry_len(&t->entry);
		update_tree_entry(t);
		if (entrylen > namelen)
			continue;
		cmp = memcmp(name, entry, entrylen);
		if (cmp > 0)
			continue;
		if (cmp < 0)
			break;
		if (entrylen == namelen) {
			oidcpy(result, &oid);
			return 0;
		}
		if (name[entrylen] != '/')
			continue;
		if (!S_ISDIR(*mode))
			break;
		if (++entrylen == namelen) {
			oidcpy(result, &oid);
			return 0;
		}
		return get_tree_entry(r, &oid, name + entrylen, result, mode);
	}
	return -1;
}