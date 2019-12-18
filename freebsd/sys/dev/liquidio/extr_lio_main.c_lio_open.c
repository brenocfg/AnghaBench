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
typedef  int /*<<< orphan*/  uint8_t ;
struct octeon_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_addr; } ;
struct lio {int intf_open; TYPE_1__ linfo; struct octeon_device* oct_dev; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ETHER_HDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  LIO_IFSTATE_RUNNING ; 
 int /*<<< orphan*/  if_setdrvflagbits (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int) ; 
 int /*<<< orphan*/  lio_dev_info (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_ifstate_set (struct lio*,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_is_mac_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_send_rx_ctrl_cmd (struct lio*,int) ; 
 int lio_set_mac (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
lio_open(void *arg)
{
	struct lio	*lio = arg;
	struct ifnet	*ifp = lio->ifp;
	struct octeon_device	*oct = lio->oct_dev;
	uint8_t	*mac_new, mac_old[ETHER_HDR_LEN];
	int	ret = 0;

	lio_ifstate_set(lio, LIO_IFSTATE_RUNNING);

	/* Ready for link status updates */
	lio->intf_open = 1;

	lio_dev_info(oct, "Interface Open, ready for traffic\n");

	/* tell Octeon to start forwarding packets to host */
	lio_send_rx_ctrl_cmd(lio, 1);

	mac_new = IF_LLADDR(ifp);
	memcpy(mac_old, ((uint8_t *)&lio->linfo.hw_addr) + 2, ETHER_HDR_LEN);

	if (lio_is_mac_changed(mac_new, mac_old)) {
		ret = lio_set_mac(ifp, mac_new);
		if (ret)
			lio_dev_err(oct, "MAC change failed, error: %d\n", ret);
	}

	/* Now inform the stack we're ready */
	if_setdrvflagbits(ifp, IFF_DRV_RUNNING, 0);

	lio_dev_info(oct, "Interface is opened\n");
}