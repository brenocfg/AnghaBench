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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dva_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVA_GET_ASIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ DVA_GET_GANG (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_IS_VALID (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENXIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_GANGBLOCKSIZE ; 
 int metaslab_claim_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vdev_lookup_top (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_psize_to_asize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
metaslab_claim_dva(spa_t *spa, const dva_t *dva, uint64_t txg)
{
	uint64_t vdev = DVA_GET_VDEV(dva);
	uint64_t offset = DVA_GET_OFFSET(dva);
	uint64_t size = DVA_GET_ASIZE(dva);
	vdev_t *vd;

	if ((vd = vdev_lookup_top(spa, vdev)) == NULL) {
		return (SET_ERROR(ENXIO));
	}

	ASSERT(DVA_IS_VALID(dva));

	if (DVA_GET_GANG(dva))
		size = vdev_psize_to_asize(vd, SPA_GANGBLOCKSIZE);

	return (metaslab_claim_impl(vd, offset, size, txg));
}