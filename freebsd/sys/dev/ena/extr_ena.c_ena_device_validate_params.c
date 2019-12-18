#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ max_mtu; int /*<<< orphan*/  mac_addr; } ;
struct ena_com_dev_get_features_ctx {TYPE_1__ dev_attr; } ;
struct ena_adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  ifp; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ if_getmtu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ena_device_validate_params(struct ena_adapter *adapter,
    struct ena_com_dev_get_features_ctx *get_feat_ctx)
{

	if (memcmp(get_feat_ctx->dev_attr.mac_addr, adapter->mac_addr,
	    ETHER_ADDR_LEN) != 0) {
		device_printf(adapter->pdev,
		    "Error, mac address are different\n");
		return (EINVAL);
	}

	if (get_feat_ctx->dev_attr.max_mtu < if_getmtu(adapter->ifp)) {
		device_printf(adapter->pdev,
		    "Error, device max mtu is smaller than ifp MTU\n");
		return (EINVAL);
	}

	return 0;
}