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
struct rdma_cm_id {int port_num; struct ib_device* device; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int cma_protocol_roce_dev_port (struct ib_device*,int const) ; 
 int rdma_start_port (struct ib_device*) ; 

__attribute__((used)) static bool cma_protocol_roce(const struct rdma_cm_id *id)
{
	struct ib_device *device = id->device;
	const int port_num = id->port_num ?: rdma_start_port(device);

	return cma_protocol_roce_dev_port(device, port_num);
}