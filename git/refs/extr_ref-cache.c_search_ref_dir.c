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
struct string_slice {size_t len; char const* str; } ;
struct ref_entry {int dummy; } ;
struct ref_dir {struct ref_entry** entries; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 struct ref_entry** bsearch (struct string_slice*,struct ref_entry**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_entry_cmp_sslice ; 
 int /*<<< orphan*/  sort_ref_dir (struct ref_dir*) ; 

int search_ref_dir(struct ref_dir *dir, const char *refname, size_t len)
{
	struct ref_entry **r;
	struct string_slice key;

	if (refname == NULL || !dir->nr)
		return -1;

	sort_ref_dir(dir);
	key.len = len;
	key.str = refname;
	r = bsearch(&key, dir->entries, dir->nr, sizeof(*dir->entries),
		    ref_entry_cmp_sslice);

	if (r == NULL)
		return -1;

	return r - dir->entries;
}