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
struct virtio_device {struct ports_device* priv; } ;
struct ports_device {int /*<<< orphan*/  config_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_multiport (struct ports_device*) ; 

__attribute__((used)) static void config_intr(struct virtio_device *vdev)
{
	struct ports_device *portdev;

	portdev = vdev->priv;

	if (!use_multiport(portdev))
		schedule_work(&portdev->config_work);
}