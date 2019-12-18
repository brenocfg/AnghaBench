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
 int /*<<< orphan*/  BUS_PROBE_LOW_PRIORITY ; 
 int /*<<< orphan*/  bmtphys_dp ; 
 int /*<<< orphan*/  bmtphys_lp ; 
 int mii_phy_dev_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bmtphy_probe(device_t dev)
{
	int	rval;

	/* Let exphy(4) take precedence for these. */
	rval = mii_phy_dev_probe(dev, bmtphys_lp, BUS_PROBE_LOW_PRIORITY);
	if (rval <= 0)
		return (rval);

	return (mii_phy_dev_probe(dev, bmtphys_dp, BUS_PROBE_DEFAULT));
}