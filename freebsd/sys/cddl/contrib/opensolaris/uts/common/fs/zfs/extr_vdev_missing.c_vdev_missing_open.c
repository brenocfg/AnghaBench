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
typedef  int /*<<< orphan*/  vdev_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

__attribute__((used)) static int
vdev_missing_open(vdev_t *vd, uint64_t *psize, uint64_t *max_psize,
    uint64_t *logical_ashift, uint64_t *physical_ashift)
{
	/*
	 * Really this should just fail.  But then the root vdev will be in the
	 * faulted state with VDEV_AUX_NO_REPLICAS, when what we really want is
	 * VDEV_AUX_BAD_GUID_SUM.  So we pretend to succeed, knowing that we
	 * will fail the GUID sum check before ever trying to open the pool.
	 */
	*psize = 0;
	*max_psize = 0;
	*logical_ashift = 0;
	*physical_ashift = 0;
	return (0);
}