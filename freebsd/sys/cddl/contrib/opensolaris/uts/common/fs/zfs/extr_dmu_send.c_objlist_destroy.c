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
struct receive_objnode {int dummy; } ;
struct objlist {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (struct receive_objnode*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 struct receive_objnode* list_remove_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
objlist_destroy(struct objlist *list)
{
	for (struct receive_objnode *n = list_remove_head(&list->list);
	    n != NULL; n = list_remove_head(&list->list)) {
		kmem_free(n, sizeof (*n));
	}
	list_destroy(&list->list);
}