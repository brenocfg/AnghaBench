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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 int vdev_read_phys (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,scalar_t__,size_t) ; 

__attribute__((used)) static int
vdev_disk_read(vdev_t *vdev, const blkptr_t *bp, void *buf,
    off_t offset, size_t bytes)
{

	return (vdev_read_phys(vdev, bp, buf,
		offset + VDEV_LABEL_START_SIZE, bytes));
}