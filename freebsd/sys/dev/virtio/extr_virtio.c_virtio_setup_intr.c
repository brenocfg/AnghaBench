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
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int VIRTIO_BUS_SETUP_INTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

int
virtio_setup_intr(device_t dev, enum intr_type type)
{

	return (VIRTIO_BUS_SETUP_INTR(device_get_parent(dev), type));
}