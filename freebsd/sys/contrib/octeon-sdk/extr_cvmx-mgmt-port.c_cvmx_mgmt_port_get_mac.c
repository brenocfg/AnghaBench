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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MGMT_PORT_INVALID_PARAM ; 
 int __cvmx_mgmt_port_num_ports () ; 
 TYPE_1__* cvmx_mgmt_port_state_ptr ; 

uint64_t cvmx_mgmt_port_get_mac(int port)
{
    if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
        return CVMX_MGMT_PORT_INVALID_PARAM;

    return cvmx_mgmt_port_state_ptr[port].mac;
}