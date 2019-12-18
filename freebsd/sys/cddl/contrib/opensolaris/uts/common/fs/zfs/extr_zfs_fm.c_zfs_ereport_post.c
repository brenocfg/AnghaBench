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
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVCH_SLEEP ; 
 int /*<<< orphan*/  FM_NVA_FREE ; 
 int /*<<< orphan*/  fm_ereport_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_nvlist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ereport_start (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zfs_ereport_post(const char *subclass, spa_t *spa, vdev_t *vd, zio_t *zio,
    uint64_t stateoroffset, uint64_t size)
{
#ifdef _KERNEL
	nvlist_t *ereport = NULL;
	nvlist_t *detector = NULL;

	zfs_ereport_start(&ereport, &detector,
	    subclass, spa, vd, zio, stateoroffset, size);

	if (ereport == NULL)
		return;

	fm_ereport_post(ereport, EVCH_SLEEP);

	fm_nvlist_destroy(ereport, FM_NVA_FREE);
	fm_nvlist_destroy(detector, FM_NVA_FREE);
#endif
}