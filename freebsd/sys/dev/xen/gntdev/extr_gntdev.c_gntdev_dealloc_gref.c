#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  gref_tree; } ;
struct ioctl_gntdev_dealloc_gref {scalar_t__ count; int /*<<< orphan*/  index; } ;
struct gntdev_gref {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  to_kill_grefs_mtx; int /*<<< orphan*/  to_kill_grefs; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 struct gntdev_gref* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gref*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gref*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gntdev_gref*,int /*<<< orphan*/ ) ; 
 TYPE_2__ cleanup_data ; 
 int /*<<< orphan*/  cleanup_task ; 
 int devfs_get_cdevpriv (void**) ; 
 struct gntdev_gref* gntdev_find_grefs (struct per_user_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ gref_next ; 
 int /*<<< orphan*/  gref_tree_head ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_file_offset (struct per_user_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
gntdev_dealloc_gref(struct ioctl_gntdev_dealloc_gref *arg)
{
	int error;
	uint32_t count;
	struct gntdev_gref *gref, *gref_tmp;
	struct per_user_data *priv_user;

	error = devfs_get_cdevpriv((void**) &priv_user);
	if (error != 0)
		return (EINVAL);

	gref = gntdev_find_grefs(priv_user, arg->index, arg->count);
	if (gref == NULL) {
		log(LOG_ERR, "Can't find requested grant-refs.");
		return (EINVAL);
	}

	/* Remove the grefs from user private data. */
	count = arg->count;
	mtx_lock(&priv_user->user_data_lock);
	mtx_lock(&cleanup_data.to_kill_grefs_mtx);
	for (; gref != NULL && count > 0; gref = gref_tmp) {
		gref_tmp = RB_NEXT(gref_tree_head, &priv_user->gref_tree, gref);
		RB_REMOVE(gref_tree_head, &priv_user->gref_tree, gref);
		STAILQ_INSERT_TAIL(&cleanup_data.to_kill_grefs, gref,
		    gref_next.list);
		count--;
	}
	mtx_unlock(&cleanup_data.to_kill_grefs_mtx);
	mtx_unlock(&priv_user->user_data_lock);
	
	taskqueue_enqueue(taskqueue_thread, &cleanup_task);
	put_file_offset(priv_user, arg->count, arg->index);

	return (0);
}