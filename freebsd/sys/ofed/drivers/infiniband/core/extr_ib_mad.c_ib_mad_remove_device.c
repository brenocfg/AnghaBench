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
struct ib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ib_agent_port_close (struct ib_device*,int) ; 
 scalar_t__ ib_mad_port_close (struct ib_device*,int) ; 
 int /*<<< orphan*/  rdma_cap_ib_mad (struct ib_device*,int) ; 
 int rdma_end_port (struct ib_device*) ; 
 int rdma_start_port (struct ib_device*) ; 

__attribute__((used)) static void ib_mad_remove_device(struct ib_device *device, void *client_data)
{
	int i;

	for (i = rdma_start_port(device); i <= rdma_end_port(device); i++) {
		if (!rdma_cap_ib_mad(device, i))
			continue;

		if (ib_agent_port_close(device, i))
			dev_err(&device->dev,
				"Couldn't close port %d for agents\n", i);
		if (ib_mad_port_close(device, i))
			dev_err(&device->dev, "Couldn't close port %d\n", i);
	}
}