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
struct virtrng_info {int hwrng_register_done; int /*<<< orphan*/  hwrng; } ;
struct virtio_device {struct virtrng_info* priv; } ;

/* Variables and functions */
 int hwrng_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtrng_scan(struct virtio_device *vdev)
{
	struct virtrng_info *vi = vdev->priv;
	int err;

	err = hwrng_register(&vi->hwrng);
	if (!err)
		vi->hwrng_register_done = true;
}