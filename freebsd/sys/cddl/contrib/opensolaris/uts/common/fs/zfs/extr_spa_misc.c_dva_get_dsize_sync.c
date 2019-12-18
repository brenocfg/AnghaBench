#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vdev_deflate_ratio; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_8__ {scalar_t__ spa_deflate; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dva_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DVA_GET_ASIZE (int /*<<< orphan*/  const*) ; 
 int DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vdev_lookup_top (TYPE_2__*,int) ; 

uint64_t
dva_get_dsize_sync(spa_t *spa, const dva_t *dva)
{
	uint64_t asize = DVA_GET_ASIZE(dva);
	uint64_t dsize = asize;

	ASSERT(spa_config_held(spa, SCL_ALL, RW_READER) != 0);

	if (asize != 0 && spa->spa_deflate) {
		uint64_t vdev = DVA_GET_VDEV(dva);
		vdev_t *vd = vdev_lookup_top(spa, vdev);
		if (vd == NULL) {
			panic(
			    "dva_get_dsize_sync(): bad DVA %llu:%llu",
			    (u_longlong_t)vdev, (u_longlong_t)asize);
		}
		dsize = (asize >> SPA_MINBLOCKSHIFT) * vd->vdev_deflate_ratio;
	}

	return (dsize);
}