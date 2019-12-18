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
struct TYPE_4__ {int (* v_phys_read ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ;int /*<<< orphan*/  spa; int /*<<< orphan*/  v_read_priv; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 size_t BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 int EIO ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int zio_checksum_verify (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*) ; 

__attribute__((used)) static int
vdev_read_phys(vdev_t *vdev, const blkptr_t *bp, void *buf,
    off_t offset, size_t size)
{
	size_t psize;
	int rc;

	if (!vdev->v_phys_read)
		return (EIO);

	if (bp) {
		psize = BP_GET_PSIZE(bp);
	} else {
		psize = size;
	}

	/*printf("ZFS: reading %zu bytes at 0x%jx to %p\n", psize, (uintmax_t)offset, buf);*/
	rc = vdev->v_phys_read(vdev, vdev->v_read_priv, offset, buf, psize);
	if (rc)
		return (rc);
	if (bp != NULL)
		return (zio_checksum_verify(vdev->spa, bp, buf));

	return (0);
}