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
typedef  int uint16_t ;
struct al_eth_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  hal_adapter; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ MDIO_PAUSE_MSEC ; 
 int MDIO_TIMEOUT_MSEC ; 
 int al_eth_mdio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*) ; 
 struct al_eth_adapter* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pause (char*,scalar_t__) ; 

__attribute__((used)) static int
al_miibus_readreg(device_t dev, int phy, int reg)
{
	struct al_eth_adapter *adapter = device_get_softc(dev);
	uint16_t value = 0;
	int rc;
	int timeout = MDIO_TIMEOUT_MSEC;

	while (timeout > 0) {
		rc = al_eth_mdio_read(&adapter->hal_adapter, adapter->phy_addr,
		    -1, reg, &value);

		if (rc == 0)
			return (value);

		device_printf_dbg(adapter->dev,
		    "mdio read failed. try again in 10 msec\n");

		timeout -= MDIO_PAUSE_MSEC;
		pause("readred pause", MDIO_PAUSE_MSEC);
	}

	if (rc != 0)
		device_printf(adapter->dev, "MDIO read failed on timeout\n");

	return (value);
}