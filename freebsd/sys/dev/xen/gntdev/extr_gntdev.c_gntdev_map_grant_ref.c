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
typedef  size_t uint32_t ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  gmap_tree; } ;
struct ioctl_gntdev_map_grant_ref {int count; int /*<<< orphan*/  index; int /*<<< orphan*/ * refs; } ;
struct ioctl_gntdev_grant_ref {int /*<<< orphan*/  ref; int /*<<< orphan*/  domid; } ;
struct gnttab_map_grant_ref {int dummy; } ;
struct gntdev_gmap {int count; int handle; int /*<<< orphan*/  file_index; struct gntdev_gmap* grant_map_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  ref; int /*<<< orphan*/  dom; } ;
typedef  int /*<<< orphan*/  ref ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 int /*<<< orphan*/  M_GNTDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gmap*) ; 
 int copyin (int /*<<< orphan*/ *,struct ioctl_gntdev_grant_ref*,int) ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  free (struct gntdev_gmap*,int /*<<< orphan*/ ) ; 
 int get_file_offset (struct per_user_data*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmap_tree_head ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gntdev_map_grant_ref(struct ioctl_gntdev_map_grant_ref *arg)
{
	uint32_t i;
	int error;
	struct gntdev_gmap *gmap;
	struct per_user_data *priv_user;

	error = devfs_get_cdevpriv((void**) &priv_user);
	if (error != 0)
		return (EINVAL);

	gmap = malloc(sizeof(*gmap), M_GNTDEV, M_WAITOK | M_ZERO);
	gmap->count = arg->count;
	gmap->grant_map_ops =
	    malloc(sizeof(struct gnttab_map_grant_ref) * arg->count,
	        M_GNTDEV, M_WAITOK | M_ZERO);

	for (i = 0; i < arg->count; i++) {
		struct ioctl_gntdev_grant_ref ref;

		error = copyin(&arg->refs[i], &ref, sizeof(ref));
		if (error != 0) {
			free(gmap->grant_map_ops, M_GNTDEV);
			free(gmap, M_GNTDEV);
			return (error);
		}
		gmap->grant_map_ops[i].dom = ref.domid;
		gmap->grant_map_ops[i].ref = ref.ref;
		gmap->grant_map_ops[i].handle = -1;
		gmap->grant_map_ops[i].flags = GNTMAP_host_map;
	}

	error = get_file_offset(priv_user, arg->count, &gmap->file_index);
	if (error != 0) {
		free(gmap->grant_map_ops, M_GNTDEV);
		free(gmap, M_GNTDEV);
		return (error);
	}

	mtx_lock(&priv_user->user_data_lock);
	RB_INSERT(gmap_tree_head, &priv_user->gmap_tree, gmap);
	mtx_unlock(&priv_user->user_data_lock);

	arg->index = gmap->file_index;

	return (error);
}