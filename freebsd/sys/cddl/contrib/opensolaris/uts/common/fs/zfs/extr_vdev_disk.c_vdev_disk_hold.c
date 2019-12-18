#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* vdev_path; unsigned long long vdev_wholedisk; int /*<<< orphan*/  vdev_devid_vp; int /*<<< orphan*/ * vdev_devid; int /*<<< orphan*/ * vdev_name_vp; int /*<<< orphan*/ * vdev_tsd; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  ddi_devid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  ddi_devid_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ddi_devid_str_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  ddi_devid_str_free (char*) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 
 int /*<<< orphan*/  ldi_vp_from_devid (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldi_vp_from_name (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  spa_config_held (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
vdev_disk_hold(vdev_t *vd)
{
	ddi_devid_t devid;
	char *minor;

	ASSERT(spa_config_held(vd->vdev_spa, SCL_STATE, RW_WRITER));

	/*
	 * We must have a pathname, and it must be absolute.
	 */
	if (vd->vdev_path == NULL || vd->vdev_path[0] != '/')
		return;

	/*
	 * Only prefetch path and devid info if the device has
	 * never been opened.
	 */
	if (vd->vdev_tsd != NULL)
		return;

	if (vd->vdev_wholedisk == -1ULL) {
		size_t len = strlen(vd->vdev_path) + 3;
		char *buf = kmem_alloc(len, KM_SLEEP);

		(void) snprintf(buf, len, "%ss0", vd->vdev_path);

		(void) ldi_vp_from_name(buf, &vd->vdev_name_vp);
		kmem_free(buf, len);
	}

	if (vd->vdev_name_vp == NULL)
		(void) ldi_vp_from_name(vd->vdev_path, &vd->vdev_name_vp);

	if (vd->vdev_devid != NULL &&
	    ddi_devid_str_decode(vd->vdev_devid, &devid, &minor) == 0) {
		(void) ldi_vp_from_devid(devid, minor, &vd->vdev_devid_vp);
		ddi_devid_str_free(minor);
		ddi_devid_free(devid);
	}
}