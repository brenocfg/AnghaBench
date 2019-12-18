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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  gref_tree; } ;
struct gntdev_gref {scalar_t__ file_index; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 struct gntdev_gref* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gref*) ; 
 struct gntdev_gref* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gref*) ; 
 int /*<<< orphan*/  gref_tree_head ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gntdev_gref*
gntdev_find_grefs(struct per_user_data *priv_user,
	uint64_t index, uint32_t count)
{
	struct gntdev_gref find_gref, *gref, *gref_start = NULL;

	find_gref.file_index = index;

	mtx_lock(&priv_user->user_data_lock);
	gref_start = RB_FIND(gref_tree_head, &priv_user->gref_tree, &find_gref);
	for (gref = gref_start; gref != NULL && count > 0; gref =
	    RB_NEXT(gref_tree_head, &priv_user->gref_tree, gref)) {
		if (index != gref->file_index)
			break;
		index += PAGE_SIZE;
		count--;
	}
	mtx_unlock(&priv_user->user_data_lock);

	if (count)
		return (NULL);
	return (gref_start);
}