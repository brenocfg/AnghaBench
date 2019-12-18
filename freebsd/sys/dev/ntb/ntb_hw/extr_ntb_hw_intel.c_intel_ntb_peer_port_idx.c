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
 int EINVAL ; 
 int intel_ntb_peer_port_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_peer_port_idx(device_t dev, int port)
{
	int peer_port;

	peer_port = intel_ntb_peer_port_number(dev, 0);
	if (peer_port == -EINVAL || port != peer_port)
		return (-EINVAL);

	return (0);
}