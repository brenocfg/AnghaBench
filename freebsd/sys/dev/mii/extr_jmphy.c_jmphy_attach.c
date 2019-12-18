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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MIIF_MACPRIV0 ; 
 int /*<<< orphan*/  MIIF_PHYPRIV0 ; 
 int /*<<< orphan*/  jmphy_funcs ; 
 scalar_t__ mii_dev_mac_match (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mii_phy_dev_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int miibus_get_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jmphy_attach(device_t dev)
{
	u_int flags;

	flags = 0;
	if (mii_dev_mac_match(dev, "jme") &&
	    (miibus_get_flags(dev) & MIIF_MACPRIV0) != 0)
		flags |= MIIF_PHYPRIV0;
	mii_phy_dev_attach(dev, flags, &jmphy_funcs, 1);
	return (0);
}