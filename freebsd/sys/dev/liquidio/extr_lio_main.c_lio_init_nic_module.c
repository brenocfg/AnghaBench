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
struct TYPE_2__ {int gmxport; } ;
struct octeon_device {int ifcount; TYPE_1__ props; } ;
struct lio_if_props {int dummy; } ;

/* Variables and functions */
 int LIO_GET_NUM_NIC_PORTS_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_get_conf (struct octeon_device*) ; 
 int lio_setup_nic_devices (struct octeon_device*) ; 

__attribute__((used)) static int
lio_init_nic_module(struct octeon_device *oct)
{
	int	num_nic_ports = LIO_GET_NUM_NIC_PORTS_CFG(lio_get_conf(oct));
	int	retval = 0;

	lio_dev_dbg(oct, "Initializing network interfaces\n");

	/*
	 * only default iq and oq were initialized
	 * initialize the rest as well
	 */

	/* run port_config command for each port */
	oct->ifcount = num_nic_ports;

	bzero(&oct->props, sizeof(struct lio_if_props));

	oct->props.gmxport = -1;

	retval = lio_setup_nic_devices(oct);
	if (retval) {
		lio_dev_err(oct, "Setup NIC devices failed\n");
		goto lio_init_failure;
	}

	lio_dev_dbg(oct, "Network interfaces ready\n");

	return (retval);

lio_init_failure:

	oct->ifcount = 0;

	return (retval);
}