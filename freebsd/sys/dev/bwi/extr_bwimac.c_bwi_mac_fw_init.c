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
struct bwi_mac {int /*<<< orphan*/ * mac_iv_ext; int /*<<< orphan*/ * mac_iv; TYPE_1__* mac_sc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int bwi_mac_fw_load_iv (struct bwi_mac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bwi_mac_fw_init(struct bwi_mac *mac)
{
	device_t dev = mac->mac_sc->sc_dev;
	int error;

	error = bwi_mac_fw_load_iv(mac, mac->mac_iv);
	if (error) {
		device_printf(dev, "load IV failed\n");
		return error;
	}

	if (mac->mac_iv_ext != NULL) {
		error = bwi_mac_fw_load_iv(mac, mac->mac_iv_ext);
		if (error)
			device_printf(dev, "load ExtIV failed\n");
	}
	return error;
}