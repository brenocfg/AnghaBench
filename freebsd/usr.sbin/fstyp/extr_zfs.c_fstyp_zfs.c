#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vp_nvlist; } ;
typedef  TYPE_1__ vdev_phys_t ;
struct TYPE_5__ {TYPE_1__ vl_vdev_phys; } ;
typedef  TYPE_2__ vdev_label_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ nvlist_unpack (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

int
fstyp_zfs(FILE *fp, char *label, size_t labelsize)
{
	vdev_label_t *vdev_label = NULL;
	vdev_phys_t *vdev_phys;
	char *zpool_name = NULL;
	nvlist_t *config = NULL;
	int err = 0;

	/*
	 * Read in the first ZFS vdev label ("L0"), located at the beginning
	 * of the vdev and extract the pool name from it.
	 *
	 * TODO: the checksum of label should be validated.
	 */
	vdev_label = (vdev_label_t *)read_buf(fp, 0, sizeof(*vdev_label));
	if (vdev_label == NULL)
		return (1);

	vdev_phys = &(vdev_label->vl_vdev_phys);

	if ((nvlist_unpack(vdev_phys->vp_nvlist, sizeof(vdev_phys->vp_nvlist),
	    &config, 0)) == 0 &&
	    (nvlist_lookup_string(config, "name", &zpool_name) == 0)) {
		strlcpy(label, zpool_name, labelsize);
	} else
		err = 1;

	nvlist_free(config);
	free(vdev_label);

	return (err);
}