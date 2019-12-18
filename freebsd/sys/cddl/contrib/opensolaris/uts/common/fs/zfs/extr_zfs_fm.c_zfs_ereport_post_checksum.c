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
typedef  int /*<<< orphan*/  zio_bad_cksum_t ;
typedef  int /*<<< orphan*/  zfs_ecksum_info_t ;
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct zio {int dummy; } ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EVCH_SLEEP ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_CHECKSUM ; 
 int /*<<< orphan*/  FM_NVA_FREE ; 
 int /*<<< orphan*/ * annotate_ecksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_ereport_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_nvlist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_ereport_start (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zfs_ereport_post_checksum(spa_t *spa, vdev_t *vd,
    struct zio *zio, uint64_t offset, uint64_t length,
    const void *good_data, const void *bad_data, zio_bad_cksum_t *zbc)
{
#ifdef _KERNEL
	nvlist_t *ereport = NULL;
	nvlist_t *detector = NULL;
	zfs_ecksum_info_t *info;

	zfs_ereport_start(&ereport, &detector,
	    FM_EREPORT_ZFS_CHECKSUM, spa, vd, zio, offset, length);

	if (ereport == NULL)
		return;

	info = annotate_ecksum(ereport, zbc, good_data, bad_data, length,
	    B_FALSE);

	if (info != NULL)
		fm_ereport_post(ereport, EVCH_SLEEP);

	fm_nvlist_destroy(ereport, FM_NVA_FREE);
	fm_nvlist_destroy(detector, FM_NVA_FREE);

	if (info != NULL)
		kmem_free(info, sizeof (*info));
#endif
}