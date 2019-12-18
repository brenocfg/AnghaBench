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
struct ena_adapter {int max_mtu; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ena_dev; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENA_DBG ; 
 int ENA_MIN_MTU ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int ena_com_set_dev_mtu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*,int) ; 
 struct ena_adapter* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
ena_change_mtu(if_t ifp, int new_mtu)
{
	struct ena_adapter *adapter = if_getsoftc(ifp);
	int rc;

	if ((new_mtu > adapter->max_mtu) || (new_mtu < ENA_MIN_MTU)) {
		device_printf(adapter->pdev, "Invalid MTU setting. "
		    "new_mtu: %d max mtu: %d min mtu: %d\n",
		    new_mtu, adapter->max_mtu, ENA_MIN_MTU);
		return (EINVAL);
	}

	rc = ena_com_set_dev_mtu(adapter->ena_dev, new_mtu);
	if (likely(rc == 0)) {
		ena_trace(ENA_DBG, "set MTU to %d\n", new_mtu);
		if_setmtu(ifp, new_mtu);
	} else {
		device_printf(adapter->pdev, "Failed to set MTU to %d\n",
		    new_mtu);
	}

	return (rc);
}