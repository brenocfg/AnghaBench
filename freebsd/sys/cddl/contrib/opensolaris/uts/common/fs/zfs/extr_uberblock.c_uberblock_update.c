#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vdev_guid_sum; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ blk_birth; } ;
struct TYPE_8__ {scalar_t__ ub_txg; TYPE_1__ ub_rootbp; scalar_t__ ub_checkpoint_txg; int /*<<< orphan*/  ub_software_version; int /*<<< orphan*/  ub_timestamp; int /*<<< orphan*/  ub_guid_sum; int /*<<< orphan*/  ub_magic; } ;
typedef  TYPE_3__ uberblock_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SPA_VERSION ; 
 int /*<<< orphan*/  UBERBLOCK_MAGIC ; 
 int /*<<< orphan*/  gethrestime_sec () ; 

boolean_t
uberblock_update(uberblock_t *ub, vdev_t *rvd, uint64_t txg)
{
	ASSERT(ub->ub_txg < txg);

	/*
	 * We explicitly do not set ub_version here, so that older versions
	 * continue to be written with the previous uberblock version.
	 */
	ub->ub_magic = UBERBLOCK_MAGIC;
	ub->ub_txg = txg;
	ub->ub_guid_sum = rvd->vdev_guid_sum;
	ub->ub_timestamp = gethrestime_sec();
	ub->ub_software_version = SPA_VERSION;
	ub->ub_checkpoint_txg = 0;

	return (ub->ub_rootbp.blk_birth == txg);
}