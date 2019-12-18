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
struct raw_object_store {int /*<<< orphan*/ * packed_git; int /*<<< orphan*/  packed_git_mru; scalar_t__ loaded_alternates; int /*<<< orphan*/ * odb_tail; scalar_t__ commit_graph_attempted; int /*<<< orphan*/ * commit_graph; int /*<<< orphan*/  replace_map; int /*<<< orphan*/  alternate_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_object_store (struct raw_object_store*) ; 
 int /*<<< orphan*/  free_commit_graph (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_object_directories (struct raw_object_store*) ; 
 int /*<<< orphan*/  oidmap_free (int /*<<< orphan*/ ,int) ; 

void raw_object_store_clear(struct raw_object_store *o)
{
	FREE_AND_NULL(o->alternate_db);

	oidmap_free(o->replace_map, 1);
	FREE_AND_NULL(o->replace_map);

	free_commit_graph(o->commit_graph);
	o->commit_graph = NULL;
	o->commit_graph_attempted = 0;

	free_object_directories(o);
	o->odb_tail = NULL;
	o->loaded_alternates = 0;

	INIT_LIST_HEAD(&o->packed_git_mru);
	close_object_store(o);
	o->packed_git = NULL;
}