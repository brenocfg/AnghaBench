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
 int /*<<< orphan*/  BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ mii_dev_mac_match (int /*<<< orphan*/ ,char*) ; 
 int mii_phy_dev_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlintphys ; 
 int /*<<< orphan*/  rlphys ; 

__attribute__((used)) static int
rlphy_probe(device_t dev)
{
	int rv;

	rv = mii_phy_dev_probe(dev, rlphys, BUS_PROBE_DEFAULT);
	if (rv <= 0)
		return (rv);

	if (mii_dev_mac_match(dev, "rl") || mii_dev_mac_match(dev, "re"))
		return (mii_phy_dev_probe(dev, rlintphys, BUS_PROBE_DEFAULT));
	return (ENXIO);
}