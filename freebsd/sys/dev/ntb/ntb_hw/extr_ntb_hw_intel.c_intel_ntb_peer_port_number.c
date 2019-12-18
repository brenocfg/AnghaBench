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
struct ntb_softc {scalar_t__ dev_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NTB_DEV_USD ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_peer_port_number(device_t dev, int pidx)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	if (pidx != 0)
		return (-EINVAL);

	return (ntb->dev_type == NTB_DEV_USD ? 1 : 0);
}