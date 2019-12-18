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
 uintptr_t BD_F_ESS ; 
 uintptr_t BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
 int ENXIO ; 
 uintptr_t SCF_PCM ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ess_probe(device_t dev)
{
	uintptr_t func, ver, r, f;

	/* The parent device has already been probed. */
	r = BUS_READ_IVAR(device_get_parent(dev), dev, 0, &func);
	if (func != SCF_PCM)
		return (ENXIO);

	r = BUS_READ_IVAR(device_get_parent(dev), dev, 1, &ver);
	f = (ver & 0xffff0000) >> 16;
	if (!(f & BD_F_ESS))
		return (ENXIO);

    	device_set_desc(dev, "ESS 18xx DSP");

	return 0;
}