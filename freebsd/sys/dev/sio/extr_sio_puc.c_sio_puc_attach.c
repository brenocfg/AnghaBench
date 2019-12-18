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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 uintptr_t DEFAULT_RCLK ; 
 int /*<<< orphan*/  PUC_IVAR_CLOCK ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int sioattach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static int
sio_puc_attach(device_t dev)
{
	uintptr_t rclk;

	if (BUS_READ_IVAR(device_get_parent(dev), dev, PUC_IVAR_CLOCK,
	    &rclk) != 0)
		rclk = DEFAULT_RCLK;
	return (sioattach(dev, 0, rclk));
}