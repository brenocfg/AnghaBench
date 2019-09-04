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
struct hashmap_iter {int dummy; } ;
struct hashmap {struct hashmap* queue; } ;
struct dir_rename_entry {int /*<<< orphan*/  new_dir; struct hashmap* dir; } ;
struct diff_queue_struct {struct diff_queue_struct* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct hashmap*) ; 
 int /*<<< orphan*/  hashmap_free (struct hashmap*,int) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct dir_rename_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void initial_cleanup_rename(struct diff_queue_struct *pairs,
				   struct hashmap *dir_renames)
{
	struct hashmap_iter iter;
	struct dir_rename_entry *e;

	hashmap_iter_init(dir_renames, &iter);
	while ((e = hashmap_iter_next(&iter))) {
		free(e->dir);
		strbuf_release(&e->new_dir);
		/* possible_new_dirs already cleared in get_directory_renames */
	}
	hashmap_free(dir_renames, 1);
	free(dir_renames);

	free(pairs->queue);
	free(pairs);
}