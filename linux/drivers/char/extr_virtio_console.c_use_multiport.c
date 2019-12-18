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
struct ports_device {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONSOLE_F_MULTIPORT ; 
 int __virtio_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool use_multiport(struct ports_device *portdev)
{
	/*
	 * This condition can be true when put_chars is called from
	 * early_init
	 */
	if (!portdev->vdev)
		return false;
	return __virtio_test_bit(portdev->vdev, VIRTIO_CONSOLE_F_MULTIPORT);
}