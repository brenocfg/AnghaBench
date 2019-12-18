#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_4__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_1__ blkptr_t ;

/* Variables and functions */
 int BP_GET_NDVAS (TYPE_1__ const*) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 scalar_t__ dva_get_dsize_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
bp_get_dsize(spa_t *spa, const blkptr_t *bp)
{
	uint64_t dsize = 0;

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);

	for (int d = 0; d < BP_GET_NDVAS(bp); d++)
		dsize += dva_get_dsize_sync(spa, &bp->blk_dva[d]);

	spa_config_exit(spa, SCL_VDEV, FTAG);

	return (dsize);
}