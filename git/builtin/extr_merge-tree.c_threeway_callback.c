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
struct traverse_info {int dummy; } ;
struct name_entry {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ both_empty (struct name_entry*,struct name_entry*) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve (struct traverse_info*,struct name_entry*,struct name_entry*) ; 
 scalar_t__ same_entry (struct name_entry*,struct name_entry*) ; 
 int /*<<< orphan*/  unresolved (struct traverse_info*,struct name_entry*) ; 

__attribute__((used)) static int threeway_callback(int n, unsigned long mask, unsigned long dirmask, struct name_entry *entry, struct traverse_info *info)
{
	/* Same in both? */
	if (same_entry(entry+1, entry+2) || both_empty(entry+1, entry+2)) {
		/* Modified, added or removed identically */
		resolve(info, NULL, entry+1);
		return mask;
	}

	if (same_entry(entry+0, entry+1)) {
		if (!is_null_oid(&entry[2].oid) && !S_ISDIR(entry[2].mode)) {
			/* We did not touch, they modified -- take theirs */
			resolve(info, entry+1, entry+2);
			return mask;
		}
		/*
		 * If we did not touch a directory but they made it
		 * into a file, we fall through and unresolved()
		 * recurses down.  Likewise for the opposite case.
		 */
	}

	if (same_entry(entry+0, entry+2) || both_empty(entry+0, entry+2)) {
		/* We added, modified or removed, they did not touch -- take ours */
		resolve(info, NULL, entry+1);
		return mask;
	}

	unresolved(info, entry);
	return mask;
}