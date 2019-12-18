#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  gmap_tree; } ;
struct ioctl_gntdev_unmap_grant_ref {int /*<<< orphan*/  index; int /*<<< orphan*/  count; } ;
struct gntdev_gmap {TYPE_1__* map; } ;
struct TYPE_6__ {int /*<<< orphan*/  to_kill_gmaps_mtx; int /*<<< orphan*/  to_kill_gmaps; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gmap*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gntdev_gmap*,int /*<<< orphan*/ ) ; 
 TYPE_3__ cleanup_data ; 
 int /*<<< orphan*/  cleanup_task ; 
 int devfs_get_cdevpriv (void**) ; 
 TYPE_2__ gmap_next ; 
 int /*<<< orphan*/  gmap_tree_head ; 
 struct gntdev_gmap* gntdev_find_gmap (struct per_user_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_file_offset (struct per_user_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gntdev_unmap_grant_ref(struct ioctl_gntdev_unmap_grant_ref *arg)
{
	int error;
	struct gntdev_gmap *gmap;
	struct per_user_data *priv_user;

	error = devfs_get_cdevpriv((void**) &priv_user);
	if (error != 0)
		return (EINVAL);

	gmap = gntdev_find_gmap(priv_user, arg->index, arg->count);
	if (gmap == NULL) {
		log(LOG_ERR, "Can't find requested grant-map.");
		return (EINVAL);
	}

	mtx_lock(&priv_user->user_data_lock);
	mtx_lock(&cleanup_data.to_kill_gmaps_mtx);
	RB_REMOVE(gmap_tree_head, &priv_user->gmap_tree, gmap);
	STAILQ_INSERT_TAIL(&cleanup_data.to_kill_gmaps, gmap, gmap_next.list);
	mtx_unlock(&cleanup_data.to_kill_gmaps_mtx);
	mtx_unlock(&priv_user->user_data_lock);
	
	if (gmap->map)
		vm_object_deallocate(gmap->map->mem);

	taskqueue_enqueue(taskqueue_thread, &cleanup_task);
	put_file_offset(priv_user, arg->count, arg->index);
	
	return (0);
}