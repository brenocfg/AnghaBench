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
struct repository {int dummy; } ;
struct hashmap {int dummy; } ;
struct file_similarity {int index; int /*<<< orphan*/  entry; struct diff_filespec* filespec; } ;
struct diff_filespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_filespec (struct repository*,struct diff_filespec*) ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct file_similarity* xmalloc (int) ; 

__attribute__((used)) static void insert_file_table(struct repository *r,
			      struct hashmap *table, int index,
			      struct diff_filespec *filespec)
{
	struct file_similarity *entry = xmalloc(sizeof(*entry));

	entry->index = index;
	entry->filespec = filespec;

	hashmap_entry_init(&entry->entry, hash_filespec(r, filespec));
	hashmap_add(table, &entry->entry);
}