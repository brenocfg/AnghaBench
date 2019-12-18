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
 int BUS_PROBE_LOW_PRIORITY ; 
 scalar_t__ BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 uintptr_t DEFAULT_RCLK ; 
 int ENXIO ; 
 int /*<<< orphan*/  PUC_IVAR_CLOCK ; 
 int /*<<< orphan*/  PUC_IVAR_TYPE ; 
 uintptr_t PUC_TYPE_SERIAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int sioprobe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int) ; 

__attribute__((used)) static int
sio_puc_probe(device_t dev)
{
	device_t parent;
	uintptr_t rclk, type;
	int error;

	parent = device_get_parent(dev);

	if (BUS_READ_IVAR(parent, dev, PUC_IVAR_TYPE, &type))
		return (ENXIO);
	if (type != PUC_TYPE_SERIAL)
		return (ENXIO);

	if (BUS_READ_IVAR(parent, dev, PUC_IVAR_CLOCK, &rclk))
		rclk = DEFAULT_RCLK;

	error = sioprobe(dev, 0, rclk, 1);
	return ((error > 0) ? error : BUS_PROBE_LOW_PRIORITY);
}