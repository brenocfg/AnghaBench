#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ v_type; } ;
typedef  TYPE_2__ vnode_t ;
struct TYPE_15__ {void* vs_aux; } ;
struct TYPE_17__ {char* vdev_path; int vdev_reopening; void* vdev_notrim; TYPE_4__* vdev_tsd; TYPE_1__ vdev_stat; int /*<<< orphan*/  vdev_spa; void* vdev_nonrot; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_18__ {TYPE_2__* vf_vnode; } ;
typedef  TYPE_4__ vdev_file_t ;
struct TYPE_19__ {int /*<<< orphan*/  va_size; int /*<<< orphan*/  va_mask; } ;
typedef  TYPE_5__ vattr_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AT_SIZE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int FOFFMAX ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 void* VDEV_AUX_BAD_LABEL ; 
 void* VDEV_AUX_OPEN_FAILED ; 
 int /*<<< orphan*/  VOP_CLOSE (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VOP_GETATTR (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 TYPE_4__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rootdir ; 
 int spa_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (TYPE_2__*,int) ; 
 int vn_openat (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vdev_file_open(vdev_t *vd, uint64_t *psize, uint64_t *max_psize,
    uint64_t *logical_ashift, uint64_t *physical_ashift)
{
	vdev_file_t *vf;
	vnode_t *vp;
	vattr_t vattr;
	int error;

	/* Rotational optimizations only make sense on block devices */
	vd->vdev_nonrot = B_TRUE;

	/*
	 * We must have a pathname, and it must be absolute.
	 */
	if (vd->vdev_path == NULL || vd->vdev_path[0] != '/') {
		vd->vdev_stat.vs_aux = VDEV_AUX_BAD_LABEL;
		return (SET_ERROR(EINVAL));
	}

	/*
	 * Reopen the device if it's not currently open.  Otherwise,
	 * just update the physical size of the device.
	 */
	if (vd->vdev_tsd != NULL) {
		ASSERT(vd->vdev_reopening);
		vf = vd->vdev_tsd;
		vp = vf->vf_vnode;
		goto skip_open;
	}

	vf = vd->vdev_tsd = kmem_zalloc(sizeof (vdev_file_t), KM_SLEEP);

	/*
	 * We always open the files from the root of the global zone, even if
	 * we're in a local zone.  If the user has gotten to this point, the
	 * administrator has already decided that the pool should be available
	 * to local zone users, so the underlying devices should be as well.
	 */
	ASSERT(vd->vdev_path != NULL && vd->vdev_path[0] == '/');
	error = vn_openat(vd->vdev_path + 1, UIO_SYSSPACE,
	    spa_mode(vd->vdev_spa) | FOFFMAX, 0, &vp, 0, 0, rootdir, -1);

	if (error) {
		vd->vdev_stat.vs_aux = VDEV_AUX_OPEN_FAILED;
		kmem_free(vd->vdev_tsd, sizeof (vdev_file_t));
		vd->vdev_tsd = NULL;
		return (error);
	}

	vf->vf_vnode = vp;

#ifdef _KERNEL
	/*
	 * Make sure it's a regular file.
	 */
	if (vp->v_type != VREG) {
#ifdef __FreeBSD__
		(void) VOP_CLOSE(vp, spa_mode(vd->vdev_spa), 1, 0, kcred, NULL);
#endif
		vd->vdev_stat.vs_aux = VDEV_AUX_OPEN_FAILED;
#ifdef __FreeBSD__
		kmem_free(vd->vdev_tsd, sizeof (vdev_file_t));
		vd->vdev_tsd = NULL;
#endif
		return (SET_ERROR(ENODEV));
	}
#endif	/* _KERNEL */

skip_open:
	/*
	 * Determine the physical size of the file.
	 */
	vattr.va_mask = AT_SIZE;
	vn_lock(vp, LK_SHARED | LK_RETRY);
	error = VOP_GETATTR(vp, &vattr, kcred);
	VOP_UNLOCK(vp, 0);
	if (error) {
		(void) VOP_CLOSE(vp, spa_mode(vd->vdev_spa), 1, 0, kcred, NULL);
		vd->vdev_stat.vs_aux = VDEV_AUX_OPEN_FAILED;
		kmem_free(vd->vdev_tsd, sizeof (vdev_file_t));
		vd->vdev_tsd = NULL;
		return (error);
	}

	vd->vdev_notrim = B_TRUE;

	*max_psize = *psize = vattr.va_size;
	*logical_ashift = SPA_MINBLOCKSHIFT;
	*physical_ashift = SPA_MINBLOCKSHIFT;

	return (0);
}