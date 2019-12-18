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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int vdev_read (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
vdev_read2(vdev_t *vdev, void *priv, off_t off, void *buf, size_t bytes)
{
	return vdev_read(vdev, priv, off, buf, bytes);
}